#include "ft_traceroute.h"

static void	get_icmp_reply(char *buffer, t_icmp_reply *icmp_reply)
{
	memcpy(&icmp_reply->iphdr, buffer, IP_HDR_SIZE);
	memcpy(&icmp_reply->icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	memcpy(&icmp_reply->original_iphdr, \
		buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, IP_HDR_SIZE);
	memcpy(&icmp_reply->original_udp_pckt, buffer + ICMP_HDR_SIZE + 2 * IP_HDR_SIZE, UDP_PCKT_SIZE);
}

static int	process_icmp_reply(char *buffer, t_icmp_reply *icmp_reply, u_int16_t original_iphdr_id)
{
	get_icmp_reply(buffer, icmp_reply);
	if (icmp_reply->original_iphdr.id == original_iphdr_id)
		return 0;
	return 1;
}

static ssize_t	recv_buffer(int recv_socket, char *buffer, \
					struct sockaddr_in *dest_addr_icmp, suseconds_t *tv_recv)
{
	struct sockaddr	*dest_addr_cast;
	socklen_t		dest_addr_len;
	ssize_t			bytes_received;

	memset(buffer, 0, BUFFER_SIZE);
	dest_addr_cast = (struct sockaddr *)dest_addr_icmp;
	dest_addr_len = sizeof(dest_addr_cast);
	bytes_received = recvfrom(recv_socket, buffer, BUFFER_SIZE, 0, \
						dest_addr_cast, &dest_addr_len);
	*tv_recv = get_time();
	return bytes_received;
}

void	receive_icmp_reply(t_traceroute *traceroute, int probe, int hop)
{
	ssize_t			bytes_received;
	char			buffer[BUFFER_SIZE];

	while (1)
	{
		bytes_received = recv_buffer(traceroute->recv_socket, buffer, \
							&traceroute->dest_addr_icmp, &traceroute->tv_recv);
		if (bytes_received == -1)
		{
			display_routing_infos(traceroute, probe, hop);
			return ;
		}
		if (!process_icmp_reply(buffer, &traceroute->icmp_reply, \
				traceroute->ip_pckt.iphdr.id))
		{
			display_routing_infos(traceroute, probe, hop);
			return ;
		}
	}
}
