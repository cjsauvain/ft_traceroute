#include "ft_traceroute.h"

static int	send_probes(int fd_socket, struct sockaddr_in *dest_addr, char *buffer)
{
	int	probes;

	probes = 0;
	while (probes < 3)
	{
		if (sendto(fd_socket, buffer, UDP_DATA_SIZE, 0, \
				(const struct sockaddr *)dest_addr, sizeof(*dest_addr)) == -1)
		{
			perror("sendto");
			return 1;//check exit value
		}
		dest_addr->sin_port = dest_addr->sin_port + htons(1);
		probes++;
	}
	return 0;
}

int	loop(t_traceroute *traceroute, char *dest_addr_str)
{
	char	buffer[BUFFER_SIZE];
	int	status;
	//int	hops;

	memcpy(buffer, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", UDP_DATA_SIZE);
	//hops = 0;
	status = send_probes(traceroute->fd_socket, &traceroute->dest_addr, buffer);
	display_traceroute_dest(dest_addr_str, traceroute->dest_addr);
	receive_icmp_reply(traceroute->fd_socket);
	/*while (hops < MAX_HOP)
	{
		set_ttl_option(traceroute->fd_socket, hops + 1);
		status = send_probes(traceroute->fd_socket, &traceroute->dest_addr, buffer);
		hops++;
	}*/
	return status;
}
