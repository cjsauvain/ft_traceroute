#include "ft_traceroute.h"

t_udp_pckt	build_udp_pckt(struct sockaddr_in dest_addr_udp)
{
	t_udp_pckt	udp_pckt;

	strcpy(udp_pckt.data, "SUPERMAN");
	udp_pckt.udphdr.source = htons(49152 + (rand() % (65535 - 49152)));
	udp_pckt.udphdr.dest = dest_addr_udp.sin_port;
	udp_pckt.udphdr.len = htons(UDP_PCKT_SIZE);
	udp_pckt.udphdr.check = 0;

	return udp_pckt;
}
