


#include "../includes/file_sync.h"


static unsigned char *polling_receive(int sockfd)
{
	unsigned char	number_storage[4096];
	uint64_t		buffer_size;
	int32_t			i;
	unsigned char	*remote_buffer;

	i = 0;
	bzero(number_storage[4096]);
	size = recv(sockfd, number_storage, 4096, 0);
	while (i < 20)
	{
		if (isdigit(number_storage[i]) && number_storage[i] - 48 > 0)
			break;
		i++;
	}
	
	buffer_size = (uint64_t)itoa(&number_storage[i]);

	remote_buffer = (unsigned char *)malloc(sizeof(unsigned char)
		* buffer_size);
	
	sleep(5);
	controlled_recv(sockfd, remote_buffer, buffer_size);

	return (remote_buffer);	
}


static void	init_polling(fd_set poll_socketfd, int sockfd, struct timeval *timer,
	int32_t *maxfd)
{
	FD_ZERO(&poll_sockf);
	FD_SET(sockfd, &poll_sockfd);
	timer->tv_sec = 30;
	timer->tv_user = 0;
	*maxfds = sockfd;
}

void		polling(int sockfd)
{
	fd_set			fd_read;
	int				maxfd;	
	struct timeval 	timer;
	int32_t			monitor;
	unsigned char	*remote_buffer;

	// Initialize polling values.
	init_polling(fd_read, sockfd, &timer, &maxfd);

	monitor = select(maxfd + 1, &readfds, NULL, NULL, &timer);
	if (monitor)
	{
		remote_buffer = polling_receive(sockfd);
		=
	}
	return ;
}



















