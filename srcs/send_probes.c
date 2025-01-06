#include "ft_traceroute.h"

static int	send_probe()
{
}

int	send_probes()
{
	int	probes;

	probes = 3;
	while (probes)
	{
		send_probe();
		probes--;
	}
}
