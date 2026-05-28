#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <arpa/inet.h>
# include <stdio.h>
#include <signal.h>

# define MAC_ADDR_LEN 6
# define ERROR_PREFIX "ft_malcolm: "

extern volatile sig_atomic_t	g_running;

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
int		check_root_privilege(void);

int	create_arp_socket(void);
int	get_available_interface_index(void);

int	wait_arp_request(int sockfd, t_malcolm_config *config);
int	send_arp_reply(int sockfd, int if_index, t_malcolm_config *config);

int	setup_signal_handler(void);

#endif
