#include "ft_malcolm.h"
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

int	create_arp_socket(void)
{
	int	sockfd;

	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sockfd < 0)
	{
		printf(ERROR_PREFIX "failed to create raw socket.\n");
		return (-1);
	}
	return (sockfd);
}
