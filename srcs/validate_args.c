#include "ft_malcolm.h"

int	validate_ft_malcolm(char **argv, t_malcolm_config *config)
{
	if (argv == NULL || config == NULL)
		return (0);
	if (!parse_ipv4(argv[1], &config->source_ip))
	{
		print_parse_ipv4_error(argv[1]);
		return (0);
	}
	if (!parse_mac(argv[2], config->source_mac))
	{
		print_parse_mac_error(argv[2]);
		return (0);
	}
	if (!parse_ipv4(argv[3], &config->target_ip))
	{
		print_parse_ipv4_error(argv[3]);
		return (0);
	}
	if (!parse_mac(argv[4], config->target_mac))
	{
		print_parse_mac_error(argv[4]);
		return (0);
	}
	return (1);
}
