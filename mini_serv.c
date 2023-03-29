#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int	sockfd;
fd_set	sockets;
char msg[42 * 4096], buff[42 * 4096 + 42];

void fatal()
{
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	close(sockfd);
	exit(1);
}

int main(int ac, char **av)
{
	if (ac != 2 )
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		return 1;
	}
	//define the server address
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0 )) == -1 )
		fatal();
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
		fatal();
	if (listen(sockfd, 128) != 0)
		fatal();
	FD_ZERO(&sockets);
	FD_SET(sockfd, &sockets);
	bzero(&buff, sizeof(buff));
	bzero(&msg, sizeof(msg));
	
	return 0;
}
