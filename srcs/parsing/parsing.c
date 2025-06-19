#include "ft_traceroute.h"
#include "libft.h"

static void	check_shortoption_arg_validity(t_opt opt_struct, char *progname)
{
	switch (opt_struct.opt_char)
	{
		case 'q':
			if (ft_strlen(opt_struct.ft_optarg) > 2
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 10)
				display_invalid_number_of_probes(progname);
			break ;
		case 'p':
			if (ft_strlen(opt_struct.ft_optarg) > 5
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 65536)
				display_invalid_dest_port(progname, opt_struct.ft_optarg);
			break ;
		case 'm':
			if (ft_strlen(opt_struct.ft_optarg) > 3
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 255)
				display_invalid_max_hop(progname, opt_struct.ft_optarg);
			break ;
		case 'f':
			if (ft_strlen(opt_struct.ft_optarg) > 3
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 255)
				display_invalid_first_hop(progname, opt_struct.ft_optarg);
			break ;
		case 'w':
			if (ft_strlen(opt_struct.ft_optarg) > 2
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 60)
				display_invalid_wait(progname, opt_struct.ft_optarg);
			break ;
	}
}

static void	short_case(t_traceroute *traceroute, t_opt opt_struct, char *progname)
{
	check_shortoption_arg_validity(opt_struct, progname);

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
			break ;
		case 'h':
			display_help_and_exit();
			break ;
	}
}

static void	check_longoption_arg_validity(t_opt opt_struct, char *progname)
{
	if (!ft_strcmp(opt_struct.opt_str, "tries")
		&& (ft_strlen(opt_struct.ft_optarg) > 2
			|| ft_atoi(opt_struct.ft_optarg) < 1
			|| ft_atoi(opt_struct.ft_optarg) > 10))
		display_invalid_number_of_probes(progname);
	else if (!ft_strcmp(opt_struct.opt_str, "port")
		&& (ft_strlen(opt_struct.ft_optarg) > 5
					|| ft_atoi(opt_struct.ft_optarg) < 1
					|| ft_atoi(opt_struct.ft_optarg) > 65536))
		display_invalid_dest_port(progname, opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "max-hop")
		&& (ft_strlen(opt_struct.ft_optarg) > 3
			|| ft_atoi(opt_struct.ft_optarg) < 1
			|| ft_atoi(opt_struct.ft_optarg) > 255))
		display_invalid_max_hop(progname, opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "first-hop")
		&& (ft_strlen(opt_struct.ft_optarg) > 3
			|| ft_atoi(opt_struct.ft_optarg) < 1
			|| ft_atoi(opt_struct.ft_optarg) > 255))
		display_invalid_first_hop(progname, opt_struct.ft_optarg);
	else if (!ft_strcmp(opt_struct.opt_str, "wait")
		&& (ft_strlen(opt_struct.ft_optarg) > 2
			|| ft_atoi(opt_struct.ft_optarg) < 1
			|| ft_atoi(opt_struct.ft_optarg) > 60))
		display_invalid_wait(progname, opt_struct.ft_optarg);
}

static void	long_case(t_traceroute *traceroute, t_opt opt_struct, char *progname)
{
	check_longoption_arg_validity(opt_struct, progname);

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

static void	update_traceroute_struct(t_traceroute *traceroute, t_opt opt_struct, \
										char *progname)
{
	if (opt_struct.type == SHORT)
		short_case(traceroute, opt_struct, progname);
	else if (opt_struct.type == LONG)
		long_case(traceroute, opt_struct, progname);
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
			update_traceroute_struct(traceroute, opt_struct, &argv[0][2]);
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
