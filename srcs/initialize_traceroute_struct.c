#include "ft_traceroute.h"

t_traceroute	initialize_traceroute_struct(char *dest_addr_str)
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

	return traceroute;
}
