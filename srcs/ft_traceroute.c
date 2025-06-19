#include "ft_traceroute.h"

int	ft_traceroute(t_traceroute traceroute, char *dest_addr_str)
{
	int	status;

	create_sockets(&traceroute.send_socket, &traceroute.recv_socket, traceroute.opt.wait);
	get_addr_structures(&traceroute, dest_addr_str, traceroute.opt.dest_port);
	traceroute.ip_pckt = build_ip_pckt(traceroute.dest_addr_udp);
	status = loop(&traceroute, dest_addr_str);

	return status;
}
