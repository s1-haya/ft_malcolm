#include "ft_malcolm.h"
#include <unistd.h>

# define EXPECTED_ARGC 5

static void	print_usage(const char *program_name)
{
	printf("Usage: %s <source ip> <source mac> <target ip> <target mac>\n",
		program_name);
}

int	main(int argc, char **argv)
{
	t_malcolm_config	config;
	int					sockfd;
	int					if_index;

	if (argc != EXPECTED_ARGC)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (!validate_ft_malcolm(argv, &config))
		return (1);
	if (!check_root_privilege())
		return (1);
	if (!setup_signal_handler())
		return (1);
	sockfd = create_arp_socket();
	if (sockfd < 0)
		return (1);
	if_index = get_available_interface_index();
	if (if_index < 0)
	{
		close(sockfd);
		return (1);
	}
	if (!wait_arp_request(sockfd, &config))
	{
		close(sockfd);
		if (g_running == 0)
			return (0);
		return (1);
	}
	if (!send_arp_reply(sockfd, if_index, &config))
	{
		close(sockfd);
		return (1);
	}
	printf("Exiting program...\n");
	close(sockfd);
	return (0);
}
