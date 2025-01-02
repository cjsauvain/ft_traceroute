#include "ft_traceroute.h"

void	display_help_and_exit(void)
{
	printf("Usage:\n  traceroute host\n");
	printf("Options:\n");
	printf("  --help     Read this help and exit\n\n");
	printf("Arguments:\n");
	printf("+   host     The host to traceroute to\n");
	exit(0);
}
