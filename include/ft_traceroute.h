#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <string.h>
# include <arpa/inet.h>
# include <errno.h>
# include <linux/udp.h>
# include <linux/icmp.h>
# include <linux/ip.h>

# define	UDP_HDR_SIZE		8
# define	UDP_DATA_SIZE		9
# define	UDP_PCKT_SIZE		UDP_HDR_SIZE + UDP_DATA_SIZE
# define	ICMP_HDR_SIZE		8
# define	IP_HDR_SIZE			20
# define	ICMP_DATA_SIZE		IP_HDR_SIZE + UDP_PCKT_SIZE
# define	MAX_HOP				64
# define	STARTING_PORT		33434
# define	LOW_PRIVATE_PORT	49152
# define	HIGH_PRIVATE_PORT	65535
# define	PROBS_TIMEOUT_SEC	3
# define	PROBS_TIMEOUT_USEC	0
# define	BUFFER_SIZE			4096

typedef struct	s_udp_pckt
{
	struct udphdr	udphdr;
	char			data[UDP_DATA_SIZE];
}	t_udp_pckt;

typedef struct	s_icmp_reply
{
	struct iphdr	iphdr;
	struct icmphdr	icmphdr;
	t_udp_pckt		udp_pckt;
}	t_icmp_reply;

typedef struct	s_traceroute
{
	int					send_socket;
	int					recv_socket;
	t_udp_pckt			udp_pckt;
	t_icmp_reply		icmp_reply;
	struct sockaddr_in	dest_addr_udp;
	struct sockaddr_in	dest_addr_icmp;
}	t_traceroute;

/*******************/
/*      ROOT       */
/*******************/
int					ft_traceroute(char *dest_addr);
int					get_addr_structures(struct sockaddr_in *dest_addr_udp, \
						struct sockaddr_in *dest_addr_icmp, char *dest_addr_str);
void 				create_sockets(int *send_socket, int *recverr_socket);
int					set_ttl_option(int send_socket, int ttl_increment);
int 				loop(t_traceroute *traceroute, char *dest_addr_str);
void    			display_traceroute_dest(char *dest_addr_str, \
						struct sockaddr_in dest_addr_udp);
void    			receive_icmp_reply(t_traceroute *traceroute);
void    			clean_exit(int send_socket, int recv_socket, \
						const char *origin, int status);
t_udp_pckt  		build_udp_pckt(struct sockaddr_in dest_addr_udp);

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
