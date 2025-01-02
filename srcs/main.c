#include "ft_traceroute.h"

int	main(int argc, char **argv)
{
	int	exit_status;

	parsing(argc, argv + 1);
	exit_status = ft_traceroute(argv[1], argv[2]);

	return exit_status;
}
