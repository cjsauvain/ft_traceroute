#include "ft_traceroute.h"

int	ft_traceroute(char *dest_addr_str)
{
	t_traceroute	traceroute;
	int				status;

	memset(&traceroute, 0, sizeof(traceroute));
	traceroute.fd_socket = create_socket();
	traceroute.dest_addr = get_addr_struct(dest_addr_str);
	//traceroute.udp_pckt = build_udp_packet();
	status = loop(&traceroute, dest_addr_str);

	return status;
}
