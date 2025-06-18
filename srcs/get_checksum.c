#include "ft_traceroute.h"
#include <string.h>

static void	put_pseudo_hdr_inside_buffer(struct iphdr iphdr, char *buffer)
{
	int offset;
	int	udp_len;

	udp_len = htons(ntohs(iphdr.tot_len) - iphdr.ihl * 4);
	offset = 0;
	memcpy(buffer + offset, &iphdr.saddr, sizeof(u_int32_t));
	offset += sizeof(u_int32_t);
	memcpy(buffer + offset, &iphdr.daddr, sizeof(u_int32_t));
	offset += sizeof(u_int32_t);
	memset(buffer + offset , 0, sizeof(u_int8_t));
	offset += sizeof(u_int8_t);
	memcpy(buffer + offset, &iphdr.protocol, sizeof(u_int8_t));
	offset += sizeof(u_int8_t);
	memcpy(buffer + offset, &udp_len, sizeof(u_int16_t));
}

static u_int16_t	process_checksum(u_int16_t *buffer)
{
	u_int32_t	sum;
	u_int16_t	checksum;
	int			len;

	sum = 0;
	len = PSEUDO_HDR_SIZE + UDP_PCKT_SIZE + 1;
	while (len > 1)
	{
		sum += *buffer++;
		len -= 2;
	}
	if (len > 0)
		sum += *(unsigned char *)buffer;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;
	return checksum;
}

u_int16_t	get_checksum(t_ip_pckt ip_pckt)
{
	u_int16_t	checksum;
	char		buffer[UDP_PCKT_SIZE + PSEUDO_HDR_SIZE + 1];

	ip_pckt.udp_pckt.udphdr.check = 0;
	memset(buffer, 0, UDP_PCKT_SIZE + PSEUDO_HDR_SIZE + 1);
	put_pseudo_hdr_inside_buffer(ip_pckt.iphdr, buffer);
	memcpy(buffer + PSEUDO_HDR_SIZE, &ip_pckt.udp_pckt.udphdr, UDP_HDR_SIZE);
	memcpy(buffer + PSEUDO_HDR_SIZE + UDP_HDR_SIZE, &ip_pckt.udp_pckt.data, UDP_DATA_SIZE);
	memset(buffer + PSEUDO_HDR_SIZE + UDP_PCKT_SIZE, 0, 1);
	checksum = process_checksum((u_int16_t *)buffer);

	return checksum;
}
