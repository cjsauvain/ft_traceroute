#include "ft_traceroute.h"

struct sockaddr_in	*get_addr_struct(char *dest_addr_str)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*dest_addr;
	int					status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	status = getaddrinfo(dest_addr_str, NULL, &hints, &res);
	if (status)
	{
		printf("%s\n", gai_strerror(status));
		exit(2);
	}
	dest_addr = (struct sockaddr_in *)&res->ai_addr;
	freeaddrinfo(res);
	return dest_addr;
}
