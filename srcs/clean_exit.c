#include "ft_traceroute.h"
#include <stdio.h>
#include <stdlib.h>

void	clean_exit(int send_socket, int recv_socket, const char *origin, int status)
{
	perror(origin);
	close(send_socket);
	close(recv_socket);
	exit(status);
}
