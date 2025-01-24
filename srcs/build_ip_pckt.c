#include "ft_traceroute.h"

static struct iphdr	build_first_ip_hdr(struct sockaddr_in dest_addr_udp)
{
	struct iphdr	iphdr;

	iphdr.ihl = 5;
	iphdr.version = 4;
	iphdr.tos = 0;
	iphdr.tot_len = htons(IP_HDR_SIZE + UDP_PCKT_SIZE);
	iphdr.id = htons(getpid());
	iphdr.frag_off = htons(0x4000);
	iphdr.ttl = 1;
	iphdr.protocol = IPPROTO_UDP;
	iphdr.check = 0;
	iphdr.saddr = 0;
	iphdr.daddr = dest_addr_udp.sin_addr.s_addr;;

	return iphdr;
}

static t_udp_pckt	build_first_udp_pckt(struct sockaddr_in dest_addr_udp)
{
	t_udp_pckt	udp_pckt;

	strcpy(udp_pckt.data, "SUPERMAN");
	udp_pckt.udphdr.source = htons(49152 + (rand() % (65535 - 49152)));
	udp_pckt.udphdr.dest = dest_addr_udp.sin_port;
	udp_pckt.udphdr.len = htons(UDP_PCKT_SIZE);
	udp_pckt.udphdr.check = 0;

	return udp_pckt;
}

t_ip_pckt	build_first_ip_pckt(struct sockaddr_in dest_addr_udp)
{
	t_ip_pckt	ip_pckt;

	ip_pckt.iphdr = build_first_ip_hdr(dest_addr_udp);
	ip_pckt.udp_pckt = build_first_udp_pckt(dest_addr_udp);
	return ip_pckt;
}
