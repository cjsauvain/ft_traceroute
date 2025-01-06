#include "ft_traceroute.h"

int	main(int argc, char **argv)
{
	char	*dest_addr;
	int		exit_status;

	srand(time(NULL));
	dest_addr = parsing(argc, argv + 1);
	exit_status = ft_traceroute(dest_addr);

	return exit_status;
}
