#include "ft_malcolm.h"
#include <unistd.h>

int	check_root_privilege(void)
{
	if (getuid() != 0)
	{
		printf(ERROR_PREFIX "this program must be run as root.\n");
		return (0);
	}
	return (1);
}
