#include "ft_malcolm.h"

static int	same_mac(const unsigned char actual[MAC_ADDR_LEN],
		const unsigned char expected[MAC_ADDR_LEN])
{
	int	i;

	i = 0;
	while (i < MAC_ADDR_LEN)
	{
		if (actual[i] != expected[i])
			return (0);
		i++;
	}
	return (1);
}

static int	check_valid_mac(const char *input,
		const unsigned char expected[MAC_ADDR_LEN])
{
	unsigned char	mac[MAC_ADDR_LEN];
	int				result;

	result = parse_mac(input, mac);
	if (result == 1 && same_mac(mac, expected))
	{
		printf("[OK]   parse_mac(\"%s\")\n", input);
		return (0);
	}
	printf("[FAIL] parse_mac(\"%s\") expected valid mac\n", input);
	return (1);
}

static int	check_invalid_mac(const char *input)
{
	unsigned char	mac[MAC_ADDR_LEN];
	int				result;

	result = parse_mac(input, mac);
	if (result == 0)
	{
		printf("[OK]   parse_mac(\"%s\")\n", input);
		return (0);
	}
	printf("[FAIL] parse_mac(\"%s\") expected invalid mac\n", input);
	return (1);
}

int	run_parse_mac_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== parse_mac tests ===\n");

	failures += check_valid_mac("aa:bb:cc:dd:ee:ff",
			(unsigned char [MAC_ADDR_LEN]){0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff});
	failures += check_valid_mac("AA:BB:CC:DD:EE:FF",
			(unsigned char [MAC_ADDR_LEN]){0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff});
	failures += check_valid_mac("16:8b:6f:6b:b6:bf",
			(unsigned char [MAC_ADDR_LEN]){0x16, 0x8b, 0x6f, 0x6b, 0xb6, 0xbf});
	failures += check_valid_mac("00:00:00:00:00:00",
			(unsigned char [MAC_ADDR_LEN]){0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
	failures += check_valid_mac("ff:ff:ff:ff:ff:ff",
			(unsigned char [MAC_ADDR_LEN]){0xff, 0xff, 0xff, 0xff, 0xff, 0xff});

	failures += check_invalid_mac("aaa:bb:cc:dd:ee:ff");
	failures += check_invalid_mac("aa:bb:cc:dd:ee");
	failures += check_invalid_mac("aa:bb:cc:dd:ee:ff:11");
	failures += check_invalid_mac("a:bb:cc:dd:ee:ff");
	failures += check_invalid_mac("aa:b:cc:dd:ee:ff");
	failures += check_invalid_mac("aa-bb-cc-dd-ee-ff");
	failures += check_invalid_mac("zz:bb:cc:dd:ee:ff");
	failures += check_invalid_mac("gg:bb:cc:dd:ee:ff");
	failures += check_invalid_mac("aa:bb:cc:dd:ee:fg");
	failures += check_invalid_mac("aa:bb:cc:dd:ee:ff ");
	failures += check_invalid_mac(" aa:bb:cc:dd:ee:ff");
	failures += check_invalid_mac("");

	return (failures);
}
