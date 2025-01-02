#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>

struct typedef	s_icmp_pckt
{
	struct icmphdr	icmphdr;
	char			data[ICMP_DATA_SIZE];
}	t_icmp_pckt;

struct typedef	s_traceroute
{
	struct iphdr	iphdr;
	t_icmp_pckt		icmp_pckt;
}	t_traceroute;

/*******************/
/*      ROOT       */
/*******************/
int		ft_traceroute(char *host, char *packet_len);

/*******************/
/*     DISPLAY     */
/*******************/
void	display_help_and_exit(void);

#endif
