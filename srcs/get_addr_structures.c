#include "ft_traceroute.h"

static int	get_addr_struct(struct sockaddr_in *dest_addr, char *dest_addr_str, int proto)
{
	struct addrinfo		hints;
	struct addrinfo		*res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if (proto == IPPROTO_UDP)
	{
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
	}
	else if (proto == IPPROTO_ICMP)
	{
		hints.ai_socktype = SOCK_RAW;
		hints.ai_protocol = IPPROTO_ICMP;
	}
	if (getaddrinfo(dest_addr_str, NULL, &hints, &res))
		return 1;
	*dest_addr = *(struct sockaddr_in *)res->ai_addr;
	dest_addr->sin_port = STARTING_PORT;
	freeaddrinfo(res);
	return 0;
}

void	get_addr_structures(t_traceroute *traceroute, char *dest_addr_str)
{
	if (get_addr_struct(&traceroute->dest_addr_udp, dest_addr_str, IPPROTO_UDP))
	{
		dprintf(2, "ft_traceroute: unknown host\n");
		close(traceroute->send_socket);
		close(traceroute->recv_socket);
		exit(1);
	}
}
