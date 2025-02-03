#include "ft_traceroute.h"

void	display_hop_number(int hop)
{
	printf("  %d", hop);
}

static void	display_spaces(int probe)
{
	if (!probe)
		printf("   ");
	else
		printf("  ");
}

static void	display_stats(t_icmp_reply icmp_reply, suseconds_t tv_sent, \
							suseconds_t tv_recv)
{
	char			*hop_ip_addr;
	static char		*prev_hop_ip_addr = NULL;
	struct in_addr	addr;
	suseconds_t		int_part;
	u_int32_t		dec_part;

	addr.s_addr = icmp_reply.iphdr.saddr;
	hop_ip_addr = inet_ntoa(addr);
	if (ft_strcmp(hop_ip_addr, prev_hop_ip_addr))
		printf("%s  ", hop_ip_addr);
	prev_hop_ip_addr = hop_ip_addr;
	int_part = (tv_recv - tv_sent) / 1000;
	dec_part = (tv_recv - tv_sent) % 1000;
	printf("%li,%.03ims", int_part, dec_part);
}

void	display_routing_infos(t_traceroute *traceroute, int probe, int hop)
{
	if (!probe)
		display_hop_number(hop);
	display_spaces(probe);
	if (traceroute->tv_recv - traceroute->tv_sent > PROBS_TIMEOUT_USEC)
	{
		printf("*");
		fflush(stdout);
	}
	else
	{
		display_stats(traceroute->icmp_reply, traceroute->tv_sent, traceroute->tv_recv);
		if (traceroute->icmp_reply.icmphdr.type == 3 && traceroute->icmp_reply.icmphdr.code == 3)
			traceroute->port_unreachable = true;
	}
	if (probe == 2)
		printf("\n");
}
