#include "ft_traceroute.h"

static t_icmp_reply	get_icmp_reply(char *buffer)
{
	t_icmp_reply	icmp_reply;

	memcpy(&icmp_reply.iphdr, buffer, IP_HDR_SIZE);
	memcpy(&icmp_reply.icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	memcpy(&icmp_reply.original_iphdr, \
		buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, IP_HDR_SIZE);
	memcpy(&icmp_reply.original_udp_pckt, buffer + ICMP_HDR_SIZE + 2 * IP_HDR_SIZE, UDP_PCKT_SIZE);

	return icmp_reply;
}

static t_icmp_reply	process_icmp_reply(char *buffer)
{
	t_icmp_reply	icmp_reply;

	icmp_reply = get_icmp_reply(buffer);
	//check_reply_validity(icmp_reply);

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
	traceroute->icmp_reply = process_icmp_reply(buffer);
	display_routing_infos(traceroute->icmp_reply);
}
