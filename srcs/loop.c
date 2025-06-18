#include "ft_traceroute.h"
#include <stdio.h>

static void	sendto_failure(int send_socket, int recv_socket, int hop)
{
	char	buffer[24];

	snprintf(buffer, 24, "  %d  traceroute: sendto", hop);
	clean_exit(send_socket, recv_socket, buffer, 1);
}

static int	send_probes(t_traceroute *traceroute, int hop)
{
	int	probes;

	probes = 0;
	while (probes < 3)
	{
		if (sendto(traceroute->send_socket, &traceroute->ip_pckt, \
				IP_HDR_SIZE + UDP_PCKT_SIZE, 0, \
				(const struct sockaddr *)&traceroute->dest_addr_udp, \
				sizeof(struct sockaddr)) == -1)
			sendto_failure(traceroute->send_socket, traceroute->recv_socket, hop);
		traceroute->tv_sent = get_time();
		receive_icmp_reply(traceroute, probes, hop);
		traceroute->ip_pckt.iphdr.id += htons(1);
		probes++;
	}
	return 0;
}

int	loop(t_traceroute *traceroute, char *dest_addr_str)
{
	int	status;
	int	hops;

	hops = 1;
	display_traceroute_dest(dest_addr_str, traceroute->dest_addr_udp);
	status = send_probes(traceroute, hops);
	while (hops < MAX_HOP && traceroute->port_unreachable == false)
	{
		hops++;
		traceroute->dest_addr_udp.sin_port++;
		traceroute->dest_addr_icmp.sin_port++;
		traceroute->ip_pckt.udp_pckt.udphdr.dest = htons(traceroute->dest_addr_udp.sin_port);
		traceroute->ip_pckt.udp_pckt.udphdr.check = get_checksum(traceroute->ip_pckt);
		traceroute->ip_pckt.iphdr.ttl++;
		status = send_probes(traceroute, hops);
	}
	return status;
}
