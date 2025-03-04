#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef unsigned char uchar;

int send_string(int sock_fd, uchar *buffer){
    int sent_bytes, bytes_to_send;
    bytes_to_send = strlen((char *)buffer);

    while(bytes_to_send > 0){
        sent_bytes = send(sock_fd, buffer, bytes_to_send, 0);
        if(sent_bytes == -1) return 0;

        bytes_to_send -= sent_bytes;
        buffer += sent_bytes;
    }

    return 1;
}

int recv_line(int sock_fd, uchar *dest_buffer){
#define EOL "\r\n"
#define EOL_SIZE 2

    uchar *ptr;
    int eol_matched = 0;

    ptr = dest_buffer;
    while(recv(sock_fd, ptr, 1, 0) == 1){
        if(*ptr == EOL[eol_matched]){
            eol_matched++;

            if(eol_matched == EOL_SIZE){
                *(ptr + 1 - EOL_SIZE) = '\0';
                return strlen((char *)dest_buffer);

            }
        } else {
            eol_matched = 0;
        }
        ptr++;
    }
    return 0;
}

