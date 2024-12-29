#include "ft_traceroute.h"

int	main(int argc, char **argv)
{
	int	exit_status;

	if (argc < 2 || argc > 3)
		display_help_and_exit();
	exit_status = ft_traceroute(argv[1], argv[2]);

	return exit_status;
}
