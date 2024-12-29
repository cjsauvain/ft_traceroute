#include "ft_traceroute.h"

void	display_help_and_exit(void)
{
	printf("Usage:\n  traceroute host [ packetlen ]\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	printf("      packetlen     The full packet length ");
	printf("(default is the length of an IP\n");
	printf("                    header plus 40). ");
	printf("Can be ignored or increased to a minimal\n");
	printf("                    allowed value\n");
}
