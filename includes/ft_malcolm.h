#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <arpa/inet.h>
# include <stdio.h>

# define MAC_ADDR_LEN 6

typedef struct s_malcolm_config
{
	struct in_addr	source_ip;
	unsigned char	source_mac[MAC_ADDR_LEN];
	struct in_addr	target_ip;
	unsigned char	target_mac[MAC_ADDR_LEN];
}	t_malcolm_config;

int		parse_ipv4(const char *str, struct in_addr *out);
void	print_parse_ipv4_error(const char *ip);

int		parse_mac(const char *str, unsigned char out[MAC_ADDR_LEN]);
void	print_parse_mac_error(const char *mac);


int		validate_ft_malcolm(char **argv, t_malcolm_config *config);

#endif
