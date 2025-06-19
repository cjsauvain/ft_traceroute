#include "ft_traceroute.h"
#include <stdio.h>
#include <stdlib.h>

static int	set_timeout_option(int recv_socket, int timeout)
{
	struct timeval	timeout_struct;
	int				status;

	timeout_struct.tv_sec = timeout;
	timeout_struct.tv_usec = 0;
	status = setsockopt(recv_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout_struct, sizeof(timeout_struct));
	return status;
}

static int	set_hdr_inc_option(int send_socket)
{
	int	opt;
	int	status;

	opt = 1;
	status = setsockopt(send_socket, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt));

	return status;
}

void	create_sockets(int *send_socket, int *recv_socket, int timeout)
{
	*send_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (*send_socket == -1)
	{
		perror("ft_traceroute: socket");
		exit(1);
	}
	*recv_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*recv_socket == -1)
	{
		perror("ft_traceroute: socket");
		close(*send_socket);
		exit(1);
	}
	if (set_timeout_option(*recv_socket, timeout) == -1)
		clean_exit(*send_socket, *recv_socket, "ft_traceroute: setsockopt", 1);
	if(set_hdr_inc_option(*send_socket) == -1)
		clean_exit(*send_socket, *recv_socket, "ft_traceroute: setsockopt", 1);
}
