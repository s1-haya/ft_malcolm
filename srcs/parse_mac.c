#include "ft_malcolm.h"

void	print_parse_mac_error(const char *mac)
{
	printf("ft_malcolm: invalid mac address: (%s)\n", mac);
}

static int	is_hex_digit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	if ('a' <= c && c <= 'f')
		return (1);
	if ('A' <= c && c <= 'F')
		return (1);
	return (0);
}

static int	hex_value(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	parse_mac(const char *str, unsigned char out[MAC_ADDR_LEN])
{
	int	i;
	int	high;
	int	low;

	if (str == 0 || out == 0)
		return (0);
	i = 0;
	while (i < MAC_ADDR_LEN)
	{
		if (!is_hex_digit(str[i * 3]) || !is_hex_digit(str[i * 3 + 1]))
			return (0);
		high = hex_value(str[i * 3]);
		low = hex_value(str[i * 3 + 1]);
		if (high < 0 || low < 0)
			return (0);
		out[i] = (unsigned char)((high << 4) | low);
		if (i < MAC_ADDR_LEN - 1 && str[i * 3 + 2] != ':')
			return (0);
		i++;
	}
	if (str[17] != '\0')
		return (0);
	return (1);
}
