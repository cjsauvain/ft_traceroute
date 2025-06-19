#include "ft_traceroute.h"
#include <stdio.h>
#include <stdlib.h>

void	display_help_and_exit(void)
{
	printf("Usage: ft_traceroute [OPTION...] HOST\n");
	printf("Print the route packets trace to network host.\n\n");
	printf("  -q, --tries=NUM             send NUM probe packets per hop (default: 3)\n");
	printf("  -p, --port=PORT             use destination PORT port (default: 33434)\n");
	printf("  -m, --max-hop=NUM           set maximal hop count (default: 64)\n");
	printf("  -f, --first-hop=NUM         set initial hop distance\n");
	printf("  -w, --wait=NUM              wait NUM seconds for response (default: 3)\n");
	printf("  -h, --help                  give this help list\n");
	exit(0);
}
