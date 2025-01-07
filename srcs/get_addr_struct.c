#include "ft_traceroute.h"

struct sockaddr_in	get_addr_struct(char *dest_addr_str)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*dest_addr;
	int					status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	status = getaddrinfo(dest_addr_str, NULL, &hints, &res);
	if (status)
	{
		printf("%s\n", gai_strerror(status));
		exit(1);//do clean exit
	}
	dest_addr = (struct sockaddr_in *)res->ai_addr;
	dest_addr->sin_port = htons(STARTING_PORT);
	freeaddrinfo(res);

	return *dest_addr;
}
