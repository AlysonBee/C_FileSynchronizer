

#include "../includes/file_sync.h"
#include "../includes/handshake.h"

int		accept_loop(int *sockfd, struct sockaddr_in socket_address)
{
	socklen_t	address_length;
	int			accept_socket;

	address_length = sizeof(socket_address);
	while (true)
	{
        printf("accepting..\n");
		accept_socket = accept(*sockfd, (struct sockaddr *)&socket_address,
			&address_length);
        
       
		if (accept_socket)
		{
			printf("accepted\n");
			return (accept_socket) ;
		}
	}
    printf("rejected\n");
	return (-1);
}

static void 	server_loop(int sockfd, 
	struct sockaddr_in socket_address)
{
	int accept_socket;

	accept_socket = accept_loop(&sockfd, socket_address);
	
	handshake(accept_socket, SERVER);


    //printf("Server spinning a daemon...\n");
    //user_loop(accept_socket, socket_address);

}


void	server(char **argv)
{
	int sockfd;
	struct sockaddr_in	socket_address;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("sockfd");
		return ;
	}

	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = INADDR_ANY;
	socket_address.sin_port = htons(atoi(argv[2]));

	if (bind(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0)
	{
		perror("bind");
		return ;
	}

	if (listen(sockfd, 5) < 0)
	{
		perror("listen");
		return ;
	}
	server_loop(sockfd, socket_address);
}
