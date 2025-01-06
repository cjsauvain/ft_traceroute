#include "ft_traceroute.h"

static int	send_probes(int fd_socket, t_ip_pckt ip_pckt)
{
	
}

int	loop(t_traceroute *traceroute, char *dest_addr_str)
{
	int	status;
	//int	hops;

	status =  0;
	/*hops = MAX_HOP;
	while (hops)
	{
		status = send_probes();
		hops--;
	}*/
	status = send_probes(traceroute->fd_socket, traceroute->ip_pckt);
	return status;
}
