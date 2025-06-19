#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <linux/udp.h>
# include <linux/icmp.h>
# include <linux/ip.h>
# include <sys/time.h>
# include <stdbool.h>
# include <ifaddrs.h>

# define	UDP_HDR_SIZE		8
# define	UDP_DATA_SIZE		9
# define	UDP_PCKT_SIZE		UDP_HDR_SIZE + UDP_DATA_SIZE
# define	ICMP_HDR_SIZE		8
# define	IP_HDR_SIZE			20
# define	PSEUDO_HDR_SIZE		12
# define	ICMP_DATA_SIZE		IP_HDR_SIZE + UDP_PCKT_SIZE
# define	LOW_PRIVATE_PORT	49152
# define	HIGH_PRIVATE_PORT	65535
# define	BUFFER_SIZE			4096
# define	MAX_IPV4_LEN		16

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

typedef struct	s_icmp_reply
{
	struct iphdr	iphdr;
	struct icmphdr	icmphdr;
	struct iphdr	original_iphdr;
	t_udp_pckt		original_udp_pckt;
}	t_icmp_reply;

typedef struct	s_options
{
	int	number_of_probes; //done
	int	dest_port; //done
	int	max_hop;
	int	first_hop;
	int	wait; //done
}	t_options;

typedef struct	s_traceroute
{
	int					send_socket;
	int					recv_socket;
	t_ip_pckt			ip_pckt;
	t_icmp_reply		icmp_reply;
	struct sockaddr_in	dest_addr_udp;
	struct sockaddr_in	dest_addr_icmp;
	suseconds_t			tv_sent;
	suseconds_t			tv_recv;
	t_options			opt;
	bool				port_unreachable;
}	t_traceroute;

/*******************/
/*      ROOT       */
/*******************/
int					ft_traceroute(t_traceroute traceroute, char *dest_addr);
void				get_addr_structures(t_traceroute *traceroute, char *dest_addr_str, int dest_port);
void 				create_sockets(int *send_socket, int *recverr_socket, int timeout);
int 				loop(t_traceroute *traceroute, char *dest_addr_str);
void    			display_traceroute_dest(char *dest_addr_str, \
						struct sockaddr_in dest_addr_udp, int max_hop);
void    			receive_icmp_reply(t_traceroute *traceroute, int probe, int hop);
void    			clean_exit(int send_socket, int recv_socket, \
						const char *origin, int status);
t_ip_pckt			build_ip_pckt(struct sockaddr_in dest_addr_udp);
void    			display_routing_infos(t_traceroute *traceroute, \
						ssize_t bytes_received, int probe, int hop);
suseconds_t 		get_time(void);
u_int16_t   		get_checksum(t_ip_pckt ip_pckt);

/*******************/
/*     PARSING     */
/*******************/
char    *parsing(int argc, char **argv, t_traceroute *traceroute);

/*******************/
/*     DISPLAY     */
/*******************/
void	display_help_and_exit(void);

#endif
