#include "ft_malcolm.h"

void	print_parse_ipv4_error(const char *ip)
{
	printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", ip);
}

int	parse_ipv4(const char *str, struct in_addr *out)
{
	if (str == 0 || out == 0)
		return (0);
	if (inet_pton(AF_INET, str, out) != 1)
		return (0);
	return (1);
}
