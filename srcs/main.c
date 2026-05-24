#include "ft_malcolm.h"

# define EXPECTED_ARGC 5

static void	print_usage(const char *program_name)
{
	printf("Usage: %s <source ip> <source mac> <target ip> <target mac>\n",
		program_name);
}

int	main(int argc, char **argv)
{
	t_malcolm_config	config;

	if (argc != EXPECTED_ARGC)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (!validate_ft_malcolm(argv, &config))
		return (1);
	printf("Arguments are valid.\n");
	return (0);
}
