#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <linux/udp.h>
# include <linux/ip.h>
# include <string.h>

# define	IP_HDR_SIZE		20
# define	UDP_HDR_SIZE	8
# define	UDP_DATA_SIZE	32
# define	IP_PCKT_SIZE	IP_HDR_SIZE + UDP_HDR_SIZE + UDP_DATA_SIZE
# define	MAX_HOP			30

typedef struct	s_udp_pckt
{
	struct udphdr	udphdr;
	char			data[UDP_DATA_SIZE];
}	t_udp_pckt;

typedef struct	s_ip_pckt
{
	struct iphdr	iphdr;
	t_udp_pckt		udp_pckt;
}	t_ip_pckt;

typedef struct	s_traceroute
{
	t_ip_pckt		ip_pckt;
	struct sockaddr	dest_addr;
	struct timeval	tv_sent;
	struct timeval	tv_received;
}	t_traceroute;

/*******************/
/*      ROOT       */
/*******************/
int		ft_traceroute(char *host);

/*******************/
/*     PARSING     */
/*******************/
char    *parsing(int argc, char **argv);

/*******************/
/*     DISPLAY     */
/*******************/
void	display_help_and_exit(void);
void	display_bad_option_and_exit(char *option, int position);

#endif
