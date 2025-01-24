#include "ft_traceroute.h"

static int	send_probes(t_traceroute *traceroute)
{
	int				probes;

	probes = 0;
	while (probes < 3)
	{
		if (sendto(traceroute->send_socket, &traceroute->ip_pckt.udp_pckt, \
				UDP_PCKT_SIZE, 0, \
				(const struct sockaddr *)&traceroute->dest_addr_udp, \
				sizeof(struct sockaddr)) == -1)
		{
			perror("ft_traceroute: sendto");//add index probes before message (check with traceroute)
			return 1;
		}
		receive_icmp_reply(traceroute);
		//traceroute->ip_pckt.iphdr.id += htons(1);
		usleep(WAIT);
		probes++;
	}
	return 0;
}

int	loop(t_traceroute *traceroute, char *dest_addr_str)
{
	int	status;
	//int	hops;

	//hops = 1;
	status = send_probes(traceroute);
	display_traceroute_dest(dest_addr_str, traceroute->dest_addr_udp);
	/*while (hops <= MAX_HOP)
	{
		traceroute->dest_addr_udp.sin_port += htons(1);
		traceroute->udp_pckt.udphdr.dest = traceroute->dest_addr_udp.sin_port;
		if (set_ttl_option(traceroute->fd_socket, hops + 1) == -1)
			clean_exit(traceroute->send_socket, traceroute->recv_socket, 1);
		status = send_probes(traceroute);
		hops++;
	}*/
	return status;
}
