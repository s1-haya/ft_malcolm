#include "ft_malcolm.h"

#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>

#define ARP_BUFFER_SIZE 65536
#define IPV4_ADDR_LEN 4
#define MAC_ADDR_LEN 6
#define ARP_DATA_SIZE (MAC_ADDR_LEN + IPV4_ADDR_LEN + MAC_ADDR_LEN + IPV4_ADDR_LEN)
#define ARP_PACKET_SIZE (sizeof(struct ethhdr) + sizeof(struct arphdr) + ARP_DATA_SIZE)

static int	same_bytes(const unsigned char *a, const unsigned char *b, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}


static int	is_arp_packet_size_valid(ssize_t size)
{
	return (size >= (ssize_t)ARP_PACKET_SIZE);
}

static int	is_arp_request_header(unsigned char *buffer, ssize_t size)
{
	struct ethhdr	*eth;
	struct arphdr	*arp;

	if (size < (ssize_t)(sizeof(struct ethhdr) + sizeof(struct arphdr)))
		return (0);
	eth = (struct ethhdr *)buffer;
	if (ntohs(eth->h_proto) != ETH_P_ARP)
		return (0);
	arp = (struct arphdr *)(buffer + sizeof(struct ethhdr));
	if (ntohs(arp->ar_op) != ARPOP_REQUEST)
		return (0);
	if (ntohs(arp->ar_hrd) != ARPHRD_ETHER)
		return (0);
	if (ntohs(arp->ar_pro) != ETH_P_IP)
		return (0);
	if (arp->ar_hln != MAC_ADDR_LEN || arp->ar_pln != IPV4_ADDR_LEN)
		return (0);
	return (1);
}

static int	is_arp_request(unsigned char *buffer, ssize_t size)
{
	if (!is_arp_packet_size_valid(size))
		return (0);
	if (!is_arp_request_header(buffer, size))
		return (0);
	return (1);
}

static int	is_expected_arp_request(unsigned char *buffer,
		ssize_t size, t_malcolm_config *config)
{
	unsigned char	*arp_data;
	unsigned char	*sender_mac;
	unsigned char	*sender_ip;
	unsigned char	*target_ip;

	if (!is_arp_request(buffer, size))
		return (0);
	arp_data = buffer + sizeof(struct ethhdr) + sizeof(struct arphdr);
	sender_mac = arp_data;
	sender_ip = sender_mac + MAC_ADDR_LEN;
	target_ip = sender_ip + IPV4_ADDR_LEN + MAC_ADDR_LEN;
	if (!same_bytes(sender_mac, config->target_mac, MAC_ADDR_LEN))
		return (0);
	if (!same_bytes(sender_ip, (unsigned char *)&config->target_ip.s_addr,
			IPV4_ADDR_LEN))
		return (0);
	if (!same_bytes(target_ip, (unsigned char *)&config->source_ip.s_addr,
			IPV4_ADDR_LEN))
		return (0);
	return (1);
}

int	wait_arp_request(int sockfd, t_malcolm_config *config)
{
	unsigned char	buffer[ARP_BUFFER_SIZE];
	ssize_t			size;

	if (config == NULL)
		return (0);

	printf("Waiting for an ARP request...\n");
	while (g_running)
	{
		size = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
		if (size < 0)
		{
			if (g_running == 0)
				return (0);
			if (errno == EINTR)
				continue ;
			printf(ERROR_PREFIX "failed to receive packet.\n");
			return (0);
		}
		if (is_expected_arp_request(buffer, size, config))
		{
			printf("An ARP request has been broadcast.\n");
			return (1);
		}
	}
	return (0);
}
