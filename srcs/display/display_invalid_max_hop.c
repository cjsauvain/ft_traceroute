#include <stdio.h>
#include <stdlib.h>

void	display_invalid_max_hop(char *progname, char *max_hop)
{
	printf("%s: invalid hops value `%s'\n", progname, max_hop);
	exit(1);
}
