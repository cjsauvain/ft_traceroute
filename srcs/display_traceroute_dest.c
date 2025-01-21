#include "ft_traceroute.h"

void	display_traceroute_dest(char *dest_addr_udp_str, struct sockaddr_in dest_addr_udp)
{
	char	*ipv4_dest_addr_udp;

	ipv4_dest_addr_udp = inet_ntoa(dest_addr_udp.sin_addr);
	printf("traceroute to %s (%s), %d hops max\n", dest_addr_udp_str, \
		ipv4_dest_addr_udp, MAX_HOP);
}
