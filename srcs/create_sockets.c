#include "ft_traceroute.h"

static int	set_timeout_option(int recv_socket)
{
	struct timeval	timeout;
	int				status;

	timeout.tv_sec = PROBS_TIMEOUT_SEC;
	timeout.tv_usec = 0;
	status = setsockopt(recv_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
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

void	create_sockets(int *send_socket, int *recv_socket)
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
	if (set_timeout_option(*recv_socket) == -1)
		clean_exit(*send_socket, *recv_socket, "ft_traceroute: setsockopt", 1);
	if(set_hdr_inc_option(*send_socket) == -1)
		clean_exit(*send_socket, *recv_socket, "ft_traceroute: setsockopt", 1);
}
