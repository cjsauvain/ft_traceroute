#include "ft_traceroute.h"

int	ft_traceroute(char *dest_addr_str)
{
	t_traceroute	traceroute;
	int				status;

	memset(&traceroute, 0, sizeof(traceroute));
	create_sockets(&traceroute.send_socket, &traceroute.recverr_socket);
	traceroute.dest_addr = get_addr_struct(dest_addr_str);
	status = loop(&traceroute, dest_addr_str);

	return status;
}
