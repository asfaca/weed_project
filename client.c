#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int ctrl_sock = 0, data_sock = 0;
    struct sockaddr_in ctrl_sock_addr, data_sock_addr;
    int fd, file_size;
    
    if(argc != 3) {
        printf("\n Error : Enter a file name to send to server \n");
        return 1;
    }

    fd = open(argv[2], O_RDONLY);
    struct stat stat_fd;
    stat(argv[2], &stat_fd);
    file_size = stat_fd.st_size;
    char file[file_size];
    
    if (read(fd, file, file_size) < 0) {
        printf("\n Error : read Failed \n");
        return 1;
    }

    if ((ctrl_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : could not create socket \n");
        return 1;
    }

    if ((data_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : could not create socket \n");
        return 1;
    }

    memset(&ctrl_sock_addr, '0', sizeof(ctrl_sock_addr));
    ctrl_sock_addr.sin_family = AF_INET;
    ctrl_sock_addr.sin_port = htons(5000);

    memset(&data_sock_addr, '0', sizeof(data_sock_addr));
    data_sock_addr.sin_family = AF_INET;
    data_sock_addr.sin_port = htons(5001);

    if (inet_pton(AF_INET, argv[1], &ctrl_sock_addr.sin_addr) <= 0) {
        printf("\n Error : ip address error \n");
        return 1;
    }

    if (inet_pton(AF_INET, argv[1], &data_sock_addr.sin_addr) <= 0) {
        printf("\n Error : ip address error \n");
        return 1;
    }

    if (connect(ctrl_sock, (struct sockaddr *)&ctrl_sock_addr, sizeof(ctrl_sock_addr)) < 0) {
        printf("\n Error : connect error \n");
        return 1;
    }

    if (write(ctrl_sock, &file_size, sizeof(int)) <0) {
        printf("\n Error : transport error \n");
        return 1;
    }
    printf("send file size integer to server.\n");

    if (connect(data_sock, (struct sockaddr *)&data_sock_addr, sizeof(data_sock_addr)) < 0) {
        printf("\n Error : connect error \n");
        return 1;
    }

    if (write(data_sock, file, file_size) < 0) {
        printf("\n Error : transport error \n");
        return 1;
    }

    return 0;
}
