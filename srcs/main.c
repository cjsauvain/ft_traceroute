#include "ft_traceroute.h"
#include "libft.h"
#include <time.h>

static t_traceroute	initialize_traceroute_struct()
{
	t_traceroute	traceroute;

	ft_memset(&traceroute, 0, sizeof(traceroute));
	traceroute.opt.number_of_probes = 3;
	traceroute.opt.dest_port = 33434;
	traceroute.opt.max_hop = 64;
	traceroute.opt.first_hop = 1;
	traceroute.opt.wait = 3;

	return traceroute;
}

int	main(int argc, char **argv)
{
	char			*dest_addr;
	int				exit_status;
	t_traceroute	traceroute;

	srand(time(NULL));

	traceroute = initialize_traceroute_struct();
	dest_addr = parsing(argc, argv, &traceroute);
	exit_status = ft_traceroute(traceroute, dest_addr);

	return exit_status;
}
