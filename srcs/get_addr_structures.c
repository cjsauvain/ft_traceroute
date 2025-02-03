#include "ft_traceroute.h"

static int	get_addr_struct(struct sockaddr_in *dest_addr, char *dest_addr_str, int proto)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	int					status;

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

	status = getaddrinfo(dest_addr_str, NULL, &hints, &res);
	if (status)
		return status;
	*dest_addr = *(struct sockaddr_in *)res->ai_addr;
	dest_addr->sin_port = STARTING_PORT;
	freeaddrinfo(res);
	return 0;
}

int	get_addr_structures(struct sockaddr_in *dest_addr_udp, \
		struct sockaddr_in *dest_addr_icmp, char *dest_addr_str)
{
	int	status;

	status = get_addr_struct(dest_addr_udp, dest_addr_str, IPPROTO_UDP);
	if (status)
		return status;
	status = get_addr_struct(dest_addr_icmp, dest_addr_str, IPPROTO_ICMP);
	return status;
}
