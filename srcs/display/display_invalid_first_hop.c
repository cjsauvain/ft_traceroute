#include <stdio.h>
#include <stdlib.h>

void	display_invalid_first_hop(char *progname, char *first_hop)
{
	printf("%s: impossible distance `%s'\n", progname, first_hop);
	exit(1);
}
