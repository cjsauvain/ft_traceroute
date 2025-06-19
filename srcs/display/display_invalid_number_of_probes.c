#include <stdio.h>
#include <stdlib.h>

void	display_invalid_number_of_probes(char *progname)
{
	printf("%s: number of tries should be between 1 and 10\n", progname);
	exit(1);
}
