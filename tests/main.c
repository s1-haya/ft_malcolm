#include "test_ft_malcolm.h"

int	main(void)
{
	int	failures;

	failures = 0;
	failures += run_parse_ipv4_tests();
	failures += run_parse_mac_tests();
	if (failures != 0)
		return (1);
	return (0);
}
