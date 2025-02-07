#include "ft_traceroute.h"

static int	check_help_option(char *option)
{
	if (strstr("help", option) && strlen(option) <= strlen("help"))
		return 0;
	return 1;
}

void	display_bad_option_and_exit(char *option)
{
	if (option[1] != '-')
		printf("ft_traceroute: invalid option -- '%c'\n", option[1]);
	else if (option[1] == '-' && !check_help_option(option + 2))
		display_help_and_exit();
	else if (option[1] == '-')
		printf("ft_traceroute: unrecognized option '%s'\n", option);
	printf("Try 'ft_traceroute --help' for more information.\n");
	exit(64);
}
