#include "ft_traceroute.h"

static void	set_sock_opt(int fd_socket)
{
	struct timeval	timeout;
	int	ttl;

	ttl = 1;
	if (setsockopt(fd_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
	{
		close(fd_socket);
		perror("setsockopt");
		exit(1);
	}
	timeout.tv_sec = PROBS_TIMEOUT_SEC;
	timeout.tv_usec = PROBS_TIMEOUT_USEC;
	if (setsockopt(fd_socket, IPPROTO_IP, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
	{
		close(fd_socket);
		perror("setsockopt");
		exit(1);
	}
}

int	create_socket(void)
{
	int	fd_socket;

	fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (fd_socket == -1)
	{
		perror("socket");
		exit(1);
	}
	set_sock_opt(fd_socket);

	return fd_socket;
}
