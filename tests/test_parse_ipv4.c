#include "ft_malcolm.h"
#include "test_ft_malcolm.h"

static int	check_ipv4_result(const char *input, int expected)
{
	struct in_addr	addr;
	int				result;

	result = parse_ipv4(input, &addr);
	if (result == expected)
	{
		printf("[OK]   parse_ipv4(\"%s\")\n", input);
		return (0);
	}
	printf("[FAIL] parse_ipv4(\"%s\") expected=%d actual=%d\n",
		input, expected, result);
	return (1);
}

int	run_parse_ipv4_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== parse_ipv4 tests ===\n");

	failures += check_ipv4_result("192.168.64.1", 1);
	failures += check_ipv4_result("10.0.0.1", 1);
	failures += check_ipv4_result("127.0.0.1", 1);
	failures += check_ipv4_result("0.0.0.0", 1);
	failures += check_ipv4_result("255.255.255.255", 1);

	failures += check_ipv4_result("999.168.64.1", 0);
	failures += check_ipv4_result("256.0.0.1", 0);
	failures += check_ipv4_result("192.168.64", 0);
	failures += check_ipv4_result("192.168.64.1.1", 0);
	failures += check_ipv4_result("192.168.64.-1", 0);
	failures += check_ipv4_result("abc", 0);
	failures += check_ipv4_result("", 0);
	failures += check_ipv4_result("192.168.64.1 ", 0);
	failures += check_ipv4_result(" 192.168.64.1", 0);

	return (failures);
}
