#include "ft_traceroute.h"

int	ft_traceroute(char *dest_addr_str)
{
	t_traceroute	traceroute;
	int				status;

	traceroute = initialize_traceroute_struct(dest_addr_str);
	traceroute.ip_pckt = build_ip_pckt(traceroute.dest_addr_udp);
	status = loop(&traceroute, dest_addr_str);

	return status;
}
