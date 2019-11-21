

#include "../includes/file_sync.h"


void	client_loop(int sockfd, struct sockaddr_in socket_address, int usertype)
{
    unsigned char   *buffer;
    bool            flag;

    printf("usertype : %d\n", usertype);
    flag = user_access_or_node(sockfd, CLIENT, usertype);
    if (flag == true)
    {
        buffer = handshake(sockfd, CLIENT);
        free(buffer);
    }
    sync_loop(sockfd, CLIENT, socket_address, -1, NULL, usertype);
	return ;
}

void	client(char **argv)
{
	int					sockfd;
	struct sockaddr_in	socket_address;
    int                 usertype; // TODO: Replace with a secure way.

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

    char *command_buffer = command_shell();
    printf("command buffer is %s\n", command_buffer);
    if (strncmp(command_buffer, "USER", 4) == 0)
        usertype = USERTYPE;
    else
        usertype = APITYPE;
    printf("usertyp %d\n", usertype);
    client_loop(sockfd, socket_address, usertype);
}
