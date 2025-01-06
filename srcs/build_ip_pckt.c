#include "ft_traceroute.h"

static uint32_t	get_source_addr(char *dest_addr_str)
{
	struct sockaddr_in	*source_addr;
	char				buffer[256];

	if (!strcmp("localhost", dest_addr_str) 
		|| !strcmp("127.0.0.1", dest_addr_str))
		return inet_addr("127.0.0.1");
	gethostname(buffer, sizeof(buffer));
	source_addr = get_addr_struct(buffer);

	return source_addr->sin_addr.s_addr;
}

static t_udp_pckt	build_udp_packet(void)
{
	t_udp_pckt	udp_pckt;

	udp_pckt.udphdr.source = rand() % (HIGH_PRIVATE_PORT - LOW_PRIVATE_PORT) \
								+ LOW_PRIVATE_PORT;
	udp_pckt.udphdr.dest = STARTING_PORT;
	udp_pckt.udphdr.len = UDP_HDR_SIZE;
	udp_pckt.udphdr.check = 0;
	strcpy(udp_pckt.data, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
	udp_pckt.udphdr.check = process_checksum((unsigned short *)&udp_pckt, \
								UDP_HDR_SIZE + UDP_DATA_SIZE);

	return udp_pckt;
}

static struct iphdr	build_ip_hdr(struct sockaddr_in *dest_addr, uint32_t source_addr)
{
	struct iphdr	iphdr;

	iphdr.ihl = 5;
	iphdr.version = 4;
	iphdr.tos = 0;
	iphdr.tot_len = IP_PCKT_SIZE;
	iphdr.id = htons(getpid() & 0xFFFF);
	iphdr.frag_off = 0;
	iphdr.ttl = 1;
	iphdr.protocol = PROT_UDP;
	iphdr.check = 0;
	iphdr.saddr = source_addr;
	iphdr.daddr = dest_addr->sin_addr.s_addr;
	iphdr.check = process_checksum((unsigned short *)&iphdr, IP_HDR_SIZE);

	return iphdr;
}

t_ip_pckt	build_ip_pckt(struct sockaddr_in *dest_addr, char *dest_addr_str)
{
	t_ip_pckt	ip_pckt;
	uint32_t	source_addr;

	memset(&ip_pckt, 0, sizeof(ip_pckt));
	source_addr = get_source_addr(dest_addr_str);
	ip_pckt.udp_pckt = build_udp_packet();
	ip_pckt.iphdr = build_ip_hdr(dest_addr, source_addr);

	return ip_pckt;
}
