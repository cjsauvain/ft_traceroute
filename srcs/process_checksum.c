#include "ft_traceroute.h"

unsigned short	process_checksum(unsigned short *icmp_pckt, int len)
{
	unsigned int	sum;
	unsigned short	checksum;

	sum = 0;
	while (len > 1)
	{
		sum += *icmp_pckt++;
		len -= 2;
	}
	if (len > 0)
		sum += *(unsigned char *)icmp_pckt;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;
	return checksum;
}
