#include "ft_traceroute.h"

static char	*process_args(char **argv)
{
	char	*dest_addr;
	int	i;

	dest_addr = NULL;
	i = 0;
	while (argv[i])
	{
		if (!strcmp(argv[i], "--help"))
			display_help_and_exit();
		else if (argv[i][0] == '-' && argv[i][2] != '-')
			display_bad_option_and_exit(argv[i], i + 1);
		else if (!dest_addr)
			dest_addr = argv[i];
		i++;
	}
	return	dest_addr;
}

char	*parsing(int argc, char **argv)
{
	char	*dest_addr;

	if (argc < 2)
		display_help_and_exit();
	dest_addr = process_args(argv);

	return dest_addr;
}
