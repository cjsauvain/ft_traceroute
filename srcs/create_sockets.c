#include "ft_traceroute.h"

void	set_ttl_option(int fd_socket, int ttl_increment)
{
	int	ttl;

	ttl = 1 + ttl_increment;
	if (setsockopt(fd_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
	{
		close(fd_socket);
		perror("setsockopt");
		exit(1);// do clean exit and close sockets
	}
}

static void	set_timeout_option(int fd_socket)
{
	struct timeval	timeout;

	timeout.tv_sec = PROBS_TIMEOUT_SEC;
	timeout.tv_usec = PROBS_TIMEOUT_USEC;
	if (setsockopt(fd_socket, IPPROTO_IP, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
	{
		close(fd_socket);
		perror("setsockopt");
		exit(1);// do clean exit and close sockets
	}
}

static void	set_recverr_option(int fd_socket)
{
	if (setsockopt(fd_socket, IPPROTO_IP, IP_RECVERR, NULL, 0) == -1)
	{
		close(fd_socket);
		perror("setsockopt");
		exit(1);// do clean exit and close sockets
	}
}

void	create_sockets(int *send_socket, int *recverr_socket)
{
	*send_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (*send_socket == -1)
	{
		perror("socket");
		exit(1);// do clean exit and close sockets
	}
	*recverr_socket = socket(AF_INET, SOCK_DGRAM, IP_RECVERR);
	if (*recverr_socket == -1)
	{
		perror("socket");
		close(*send_socket);
		exit(1);// do clean exit and close sockets
	}
	set_ttl_option(*send_socket, 0);
	set_timeout_option(*recverr_socket);
	set_recverr_option(*recverr_socket);
}
