#ifndef	FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>

/*******************/
/*      ROOT       */
/*******************/
int		ft_traceroute(char *host, char *packet_len);

/*******************/
/*     DISPLAY     */
/*******************/
void	display_help_and_exit(void);

#endif
