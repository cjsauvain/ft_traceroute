#include "ft_traceroute.h"

void	process_args(char **argv)
{
}

void	parsing(int argc, char **argv)
{
	if (argc < 2)
	{
		display_help_and_exit();
		return -1;
	}
	process_args(argv);

	return 0;
}
