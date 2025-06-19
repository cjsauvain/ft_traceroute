#include "ft_traceroute.h"
#include "libft.h"

static void	short_case(t_traceroute *traceroute, t_opt opt_struct)
{
	switch (opt_struct.opt_char)
	{
		case 'q':
			traceroute->opt.number_of_probes = ft_atoi(opt_struct.ft_optarg);
			break ;
		case 'p':
			traceroute->opt.dest_port = ft_atoi(opt_struct.ft_optarg);
			break ;
		case 'm':
			traceroute->opt.max_hop = ft_atoi(opt_struct.ft_optarg);
			break ;
		case 'f':
			traceroute->opt.first_hop = ft_atoi(opt_struct.ft_optarg);
			break ;
		case 'w':
			traceroute->opt.wait = ft_atoi(opt_struct.ft_optarg);
		case 'h':
			display_help_and_exit();
			break ;
	}
}

static void	long_case(t_traceroute *traceroute, t_opt opt_struct)
{
	if (!ft_strcmp(opt_struct.opt_str, "tries"))
		traceroute->opt.number_of_probes = ft_atoi(opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "port"))
		traceroute->opt.dest_port = ft_atoi(opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "max-hop"))
		traceroute->opt.max_hop = ft_atoi(opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "first-hop"))
		traceroute->opt.first_hop = ft_atoi(opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "wait"))
		traceroute->opt.wait = ft_atoi(opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "help"))
		display_help_and_exit();
}

static void	update_traceroute_struct(t_traceroute *traceroute, t_opt opt_struct)
{
	if (opt_struct.type == SHORT)
		short_case(traceroute, opt_struct);
	else if (opt_struct.type == LONG)
		long_case(traceroute, opt_struct);
}

static char	*process_args(int argc, char **argv, t_traceroute *traceroute)
{
	t_opt	opt_struct;
	int		i;
	char	*dest_addr;
	char	optshort[] = "q:p:m:f:w:h";
	char	*optlong[] = {
		"tries:",
		"port:",
		"max-hop:",
		"first-hop:",
		"wait:",
		"help",
		NULL,
	};

	dest_addr = NULL;
	i = 0;
	while (i < argc)
	{
		opt_struct = ft_getopt(argc, argv, optshort, optlong);
		if (opt_struct.type != NONE)
			update_traceroute_struct(traceroute, opt_struct);
		if (i && argv[i][0] != '-' && argv[i - 1][0] != '-')
			dest_addr = argv[i];
		i++;
	}
	return	dest_addr;
}

char	*parsing(int argc, char **argv, t_traceroute *traceroute)
{
	char	*dest_addr;

	if (argc < 2)
		display_help_and_exit();
	dest_addr = process_args(argc, argv, traceroute);

	return dest_addr;
}
