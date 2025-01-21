#include "ft_traceroute.h"

static t_icmp_reply	get_icmp_reply(char *buffer)
{
	t_icmp_reply	icmp_reply;

	memset(&icmp_reply.iphdr, 0, IP_HDR_SIZE);
	memset(&icmp_reply.icmphdr, 0, ICMP_HDR_SIZE);
	memset(&icmp_reply.iphdr, 0, IP_HDR_SIZE);
	memset(&icmp_reply.udp_pckt, 0, UDP_PCKT_SIZE);

	memcpy(&icmp_reply.icmphdr, buffer, ICMP_HDR_SIZE);
	memcpy(&icmp_reply.iphdr, buffer + ICMP_HDR_SIZE, IP_HDR_SIZE);
	memcpy(&icmp_reply.udp_pckt, buffer + ICMP_HDR_SIZE + IP_HDR_SIZE, UDP_PCKT_SIZE);

	return icmp_reply;
}

void	receive_icmp_reply(t_traceroute *traceroute)
{
	ssize_t			bytes_received;
	char			buffer[BUFFER_SIZE];
	struct sockaddr	*dest_addr_cast;
	socklen_t		dest_addr_len;

	memset(buffer, 0, BUFFER_SIZE);
	dest_addr_cast = (struct sockaddr *)&traceroute->dest_addr_icmp;
	dest_addr_len = sizeof(dest_addr_cast);
	bytes_received = recvfrom(traceroute->recv_socket, buffer, BUFFER_SIZE, \
						0, dest_addr_cast, &dest_addr_len);
	if (bytes_received == -1)
		clean_exit(traceroute->send_socket, traceroute->recv_socket, "ft_traceroute: recvfrom", 1);
	traceroute->icmp_reply = get_icmp_reply(buffer);
}
