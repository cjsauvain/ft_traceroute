#include <stdio.h>
#include <stdlib.h>

void	display_invalid_dest_port(char *progname, char *dest_port)
{
	printf("%s: invalid port number `%s'\n", progname, dest_port);
	exit(1);
}
