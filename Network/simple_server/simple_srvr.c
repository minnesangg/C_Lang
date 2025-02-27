#include <hacking.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7890

int main(void) {
    int sock_fd, new_sockfd;
    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int recv_length = 1, yes = 1;
    char buffer[1024];

    if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket");
    
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("because of REUSEADDR parameter");

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = INADDR_ANY; 
    memset(&(host_addr.sin_zero), '\0', 8);

    if (bind(sock_fd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
        fatal("connecting with socket");

    if (listen(sock_fd, 5) == -1)
        fatal("listening from socket's side");

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
        if (new_sockfd == -1)
            fatal("accepting connection");

        printf("server: has been connected %s port %d\n", 
                inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        send(new_sockfd, "Hello World!\n", 13, 0);

        recv_length = recv(new_sockfd, buffer, 1024, 0);
        while (recv_length > 0) {
            printf("recv: %d bytes\n", recv_length);
            fwrite(buffer, 1, recv_length, stdout); 
            recv_length = recv(new_sockfd, buffer, 1024, 0);
        }
        close(new_sockfd);
    }

    close(sock_fd);  
    return 0;
}
