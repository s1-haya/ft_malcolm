#include "ft_malcolm.h"

#include <ifaddrs.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <stdio.h>

static int	is_available_interface(struct ifaddrs *ifa)
{
	if (ifa == NULL || ifa->ifa_addr == NULL)
		return (0);
	if (ifa->ifa_addr->sa_family != AF_PACKET)
		return (0);
	if (!(ifa->ifa_flags & IFF_UP))
		return (0);
	if (ifa->ifa_flags & IFF_LOOPBACK)
		return (0);
	return (1);
}

static int	get_interface_index(struct ifaddrs *ifa)
{
	unsigned int	index;

	index = if_nametoindex(ifa->ifa_name);
	if (index == 0)
		return (-1);
	printf("Found available interface: %s\n", ifa->ifa_name);
	return ((int)index);
}

int	get_available_interface_index(void)
{
	struct ifaddrs	*ifaddr;
	struct ifaddrs	*ifa;
	int				index;

	if (getifaddrs(&ifaddr) != 0)
	{
		printf(ERROR_PREFIX "failed to get network interfaces.\n");
		return (-1);
	}
	ifa = ifaddr;
	while (ifa != NULL)
	{
		if (is_available_interface(ifa))
		{
			index = get_interface_index(ifa);
			if (index >= 0)
			{
				freeifaddrs(ifaddr);
				return (index);
			}
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifaddr);
	printf(ERROR_PREFIX "no available network interface found.\n");
	return (-1);
}
