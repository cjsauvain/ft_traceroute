#include "ft_traceroute.h"

static u_int32_t	get_saddr(struct sockaddr_in dest_addr)
{
	int					tmp_socket;
	struct sockaddr_in	source_addr;
	socklen_t			source_addr_len;

	tmp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (tmp_socket == -1)
		return 0;//do clean exit
	if (connect(tmp_socket, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1)
		return 0;//do clean exit
	source_addr_len = sizeof(source_addr);
	if (getsockname(tmp_socket, (struct sockaddr *)&source_addr, &source_addr_len) == -1)
		return 0;//do clean exit

	return source_addr.sin_addr.s_addr;
}

static struct iphdr	build_ip_hdr(struct sockaddr_in dest_addr_udp)
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
	iphdr.saddr = get_saddr(dest_addr_udp);
	iphdr.daddr = dest_addr_udp.sin_addr.s_addr;

	return iphdr;
}

static t_udp_pckt	build_udp_pckt(struct sockaddr_in dest_addr_udp)
{
	t_udp_pckt	udp_pckt;

	strcpy(udp_pckt.data, "SUPERMAN");
	udp_pckt.udphdr.source = htons(LOW_PRIVATE_PORT + (rand() \
								% (HIGH_PRIVATE_PORT - LOW_PRIVATE_PORT)));
	udp_pckt.udphdr.dest = htons(dest_addr_udp.sin_port);
	udp_pckt.udphdr.len = htons(UDP_PCKT_SIZE);
	udp_pckt.udphdr.check = 0;

	return udp_pckt;
}

t_ip_pckt	build_ip_pckt(struct sockaddr_in dest_addr_udp)
{
	t_ip_pckt	ip_pckt;

	ip_pckt.iphdr = build_ip_hdr(dest_addr_udp);
	ip_pckt.udp_pckt = build_udp_pckt(dest_addr_udp);
	ip_pckt.udp_pckt.udphdr.check = get_checksum(ip_pckt);

	return ip_pckt;
}
