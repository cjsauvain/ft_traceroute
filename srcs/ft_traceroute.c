#include "ft_traceroute.h"

int	ft_traceroute(char *dest_addr_str)
{
	t_traceroute	traceroute;
	int				status;

	traceroute.fd_socket = create_socket();
	memset(&traceroute, 0, sizeof(traceroute));
	traceroute.dest_addr = get_addr_struct(dest_addr_str);
	traceroute.ip_pckt = build_ip_pckt(traceroute.dest_addr, dest_addr_str);
	status = loop(&traceroute, dest_addr_str);
	return 0;
}
