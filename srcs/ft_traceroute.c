#include "ft_traceroute.h"

int	ft_traceroute(char *dest_addr_str)
{
	t_traceroute	traceroute;
	int				status;

	memset(&traceroute, 0, sizeof(traceroute));
	create_sockets(&traceroute.send_socket, &traceroute.recv_socket);
	status = get_addr_structures(&traceroute.dest_addr_udp, \
				&traceroute.dest_addr_icmp, dest_addr_str);
	if (status)
		clean_exit(traceroute.send_socket, traceroute.recv_socket, \
					gai_strerror(status), 1);
	traceroute.udp_pckt = build_udp_pckt(traceroute.dest_addr_udp);
	status = loop(&traceroute, dest_addr_str);

	return status;
}
