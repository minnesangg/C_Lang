#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <hacking.h>

int main(void){
    int recv_length, sockfd;
    u_char buffer[9000];

    if((sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
        fatal("in socket");
    
    for(int i =0; i < 3; i++){
        recv_length = recv(sockfd, buffer, 8000, 0);
        printf("Received package with size %d bytes\n", recv_length);
        dump(buffer, recv_length);
    }

}