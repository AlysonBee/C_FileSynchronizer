

#include "../includes/file_sync.h"

static int		usage(char *program_name)
{
	printf("Usage: %s [-C, -S] if -C then : <port number> else if -C then : <server address> <port number>\n",
		program_name);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc < 3)
		return (usage(argv[0]));

	// Determine if this side of the connection is the client or server.	
	if (strcmp(parse_command_line_flags(argc, argv), "S") == 0)
		server(argv);
	else if (strcmp(parse_command_line_flags(argc, argv), "C") == 0)
		client(argv);
	else
		return (usage(argv[0]));
	return (0);
}


