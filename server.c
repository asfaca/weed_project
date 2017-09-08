#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int detect_weed(void *data);

int main(void) {
	int listenfd = 0, connfd = 0;
	//data
	int datafd = 0, conn_datafd = 0;
	//data
	struct sockaddr_in serv_addr;
	struct sockaddr_in serv_addr_data;
	struct sockaddr_in client_addr;

	int size_buff;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	//data
	datafd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr_data, '0', sizeof(serv_addr_data));
	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);
	//data
	serv_addr_data.sin_family = AF_INET;
	serv_addr_data.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr_data.sin_port = htons(5001);


	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//data
	bind(datafd, (struct sockaddr*)&serv_addr_data, sizeof(serv_addr));

	listen(listenfd, 5);
	//data
	listen(datafd, 5);

	while(1) {
		int len = sizeof(client_addr);
		connfd = accept(listenfd, (struct sockaddr*)&client_addr, &len);
		//data
		conn_datafd = accept(datafd, (struct sockaddr*)NULL, NULL);
		
		int read_byte = read(connfd, &size_buff, sizeof(int));
		printf("\nread byte = %d", read_byte);
		printf("\nsize buffer =  %d\n", size_buff);
		
		char read_buff[size_buff];
		memset(read_buff, '0', size_buff);
		int read_data_byte = read(conn_datafd, read_buff, size_buff);
		printf("\nread file  =  \n");
		printf("\n%s\n", read_buff);

		printf("client port : %d\n", client_addr.sin_port);

		char ipAddr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_addr.sin_addr), ipAddr, INET_ADDRSTRLEN);

		printf("client IP address : %s\n", ipAddr);
		
		//get client's ip address and port number
		
		detect_weed(read_buff);


		close(connfd);
		close(conn_datafd);
		usleep(500);
	}
	return 0;
}
