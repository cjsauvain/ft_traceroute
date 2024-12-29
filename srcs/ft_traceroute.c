#include "ft_traceroute.h"

static int	get_packet_len(char *packet_len)
{
	int	len;
	int	i;

	i = 0;
	if (strlen(packet_len) > 5)
		return -1;
	while (packet_len[i])
	{
		if (!isdigit(packet_len[i]))
			return 60;
		i++;
	}
	len = atoi(packet_len);
	if (len > 65000)
		return -1;
	if (len <= 28)
		return 60;
	return len;
}

int	ft_traceroute(char *host, char *packet_len)
{
	int	packet_len;

	packet_len = get_packet_len(packet_len); //Put into a structure
	if (packet_len == -1)
	{
		printf("too big packetlen %d specified\n", atoi(packet_len));
		return 2;
	}
	return 0;
}
