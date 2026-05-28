#include "ft_malcolm.h"

#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t	g_running = 1;

static void	zero_bytes(void *ptr, int len)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
}

static void	handle_sigint(int signum)
{
	(void)signum;
	g_running = 0;
}

int	setup_signal_handler(void)
{
	struct sigaction	sa;

	zero_bytes(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
	{
		printf(ERROR_PREFIX "failed to setup signal handler.\n");
		return (0);
	}
	return (1);
}
