#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <linux/udp.h>
# include <linux/ip.h>
# include <string.h>
# include <arpa/inet.h>

# define	IP_HDR_SIZE			20
# define	UDP_HDR_SIZE		8
# define	UDP_DATA_SIZE		32
# define	IP_PCKT_SIZE		IP_HDR_SIZE + UDP_HDR_SIZE + UDP_DATA_SIZE
# define	MAX_HOP				30
# define	PROT_UDP			17
# define	STARTING_PORT		33434
# define	LOW_PRIVATE_PORT	49152
# define	HIGH_PRIVATE_PORT	65535
# define	PROBS_TIMEOUT_SEC	5
# define	PROBS_TIMEOUT_USEC	0

typedef struct	s_udp_pckt
{
	struct udphdr	udphdr;
	char			data[UDP_DATA_SIZE + 1];
}	t_udp_pckt;

typedef struct	s_ip_pckt
{
	struct iphdr	iphdr;
	t_udp_pckt		udp_pckt;
}	t_ip_pckt;

typedef struct	s_stats
{
	struct timeval	tv_sent;
	struct timeval	tv_received;
}	t_stats;

typedef struct	s_traceroute
{
	int					fd_socket;
	t_ip_pckt			ip_pckt;
	struct sockaddr_in	*dest_addr;
	t_stats				stats;
}	t_traceroute;

/*******************/
/*      ROOT       */
/*******************/
int					ft_traceroute(char *dest_addr);
struct sockaddr_in  *get_addr_struct(char *dest_addr_str);
t_ip_pckt   		build_ip_pckt(struct sockaddr_in *dest_addr, \
						char *dest_addr_str);
unsigned short  	process_checksum(unsigned short *icmp_pckt, int len);

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
