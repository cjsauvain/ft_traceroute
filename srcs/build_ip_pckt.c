#include "ft_traceroute.h"
#include "libft.h"

static in_addr_t	get_localhost_addr(void)
{
	struct in_addr	localhost_addr;

	if (inet_pton(AF_INET, "127.0.0.1", &localhost_addr) == -1)
		perror("inet_pton");
	return localhost_addr.s_addr;
}

static u_int32_t	get_saddr(struct sockaddr_in dest_addr_udp)
{
	struct ifaddrs		*interfaces, *cursor;
	in_addr_t			localhost_addr;
	struct sockaddr_in	*cursor_addrin;
	u_int32_t			saddr;
	
	localhost_addr = get_localhost_addr();
	if (localhost_addr <= 0)
		return 0;
	if (dest_addr_udp.sin_addr.s_addr == localhost_addr 
			|| !dest_addr_udp.sin_addr.s_addr)
		return localhost_addr;
	if (getifaddrs(&interfaces) == -1)
	{
		perror("getifcursor_addrs");
		return 0;
	}
	for (cursor = interfaces; cursor; cursor = cursor->ifa_next)
	{
		if (ft_strcmp(cursor->ifa_name, "lo") && cursor->ifa_addr->sa_family == AF_INET)
			break;
	}
	cursor_addrin = (struct sockaddr_in *)cursor->ifa_addr;
	saddr = cursor_addrin->sin_addr.s_addr;
	freeifaddrs(interfaces);
	return saddr;
}

static struct iphdr	build_ip_hdr(struct sockaddr_in dest_addr_udp, int first_hop)
{
	struct iphdr	iphdr;

	iphdr.ihl = 5;
	iphdr.version = 4;
	iphdr.tos = 0;
	iphdr.tot_len = htons(IP_HDR_SIZE + UDP_PCKT_SIZE);
	iphdr.id = htons(getpid());
	iphdr.frag_off = htons(0x4000);
	iphdr.ttl = first_hop;
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

t_ip_pckt	build_ip_pckt(struct sockaddr_in dest_addr_udp, int first_hop)
{
	t_ip_pckt	ip_pckt;

	ip_pckt.iphdr = build_ip_hdr(dest_addr_udp, first_hop);
	ip_pckt.udp_pckt = build_udp_pckt(dest_addr_udp);
	ip_pckt.udp_pckt.udphdr.check = get_checksum(ip_pckt);

	return ip_pckt;
}
