#include "ft_traceroute.h"
#include <stdio.h>
#include <stdlib.h>

void	display_help_and_exit(void)
{
	printf("Usage: ft_traceroute [OPTION...] HOST\n");
	printf("Print the route packets trace to network host.\n\n");
	printf("  --help     give this help list\n");
	exit(0);
}
