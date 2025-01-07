#include "ft_traceroute.h"

void	display_traceroute_dest(char *dest_addr_str, struct sockaddr_in dest_addr)
{
	char	*ipv4_dest_addr;

	ipv4_dest_addr = inet_ntoa(dest_addr.sin_addr);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n", \
			dest_addr_str, ipv4_dest_addr, MAX_HOP, \
			UDP_PCKT_SIZE + IP_HDR_SIZE);
}
