

#include "../includes/file_sync.h"


void	client_loop(int sockfd, struct sockaddr_in socket_address)
{
//	handshake(sockfd, CLIENT);

    sync_loop(sockfd, CLIENT, socket_address);
	return ;
}

void	client(char **argv)
{
	int					sockfd;
	struct sockaddr_in	socket_address;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		return ;
	}

	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(argv[2]);
	socket_address.sin_port = htons(atoi(argv[3]));
	
	if (connect(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0)
	{
		perror("connect");
		return ;
	}
	client_loop(sockfd, socket_address);
}
