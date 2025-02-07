#include "ft_traceroute.h"

t_traceroute	initialize_traceroute_struct(char *dest_addr_str)
{
	t_traceroute	traceroute;

	memset(&traceroute, 0, sizeof(traceroute));
	create_sockets(&traceroute.send_socket, &traceroute.recv_socket);
	get_addr_structures(&traceroute, dest_addr_str);
	return traceroute;
}
