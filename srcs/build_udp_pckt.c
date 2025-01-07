#include "ft_traceroute.h"

/*static uint32_t	get_source_addr(char *dest_addr_str)
{
	struct sockaddr_in	*source_addr;
	char				buffer[256];

	if (!strcmp("localhost", dest_addr_str) 
		|| !strcmp("127.0.0.1", dest_addr_str))
		return inet_addr("127.0.0.1");
	gethostname(buffer, sizeof(buffer));
	source_addr = get_addr_struct(buffer);

	return source_addr->sin_addr.s_addr;
}*/

/*t_udp_pckt	build_udp_packet(void)
{
	t_udp_pckt	udp_pckt;

	udp_pckt.udphdr.source = htons(rand() % (HIGH_PRIVATE_PORT - LOW_PRIVATE_PORT) \
								+ LOW_PRIVATE_PORT);
	udp_pckt.udphdr.dest = htons(STARTING_PORT);
	udp_pckt.udphdr.len = htons(UDP_HDR_SIZE);
	udp_pckt.udphdr.check = 0;
	strcpy(udp_pckt.data, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
	udp_pckt.udphdr.check = process_checksum((unsigned short *)&udp_pckt, \
								UDP_HDR_SIZE + UDP_DATA_SIZE);

	return udp_pckt;
}*/
