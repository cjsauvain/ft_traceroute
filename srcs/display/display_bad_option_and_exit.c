#include "ft_traceroute.h"

void	display_bad_option_and_exit(char *option, int position)
{
	if (option[1] == '-')
		printf("Bad option `--%s' (argc %d)\n", option + 2, position);
	else
		printf("Bad option `-%c' (argc %d)\n", option[1], position);
	exit(2);
}
