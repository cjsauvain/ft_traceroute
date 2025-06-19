#include <stdio.h>
#include <stdlib.h>

void	display_invalid_wait(char *progname, char *wait)
{
	printf("%s: ridiculous waiting time `%s'\n", progname, wait);
	exit(1);
}
