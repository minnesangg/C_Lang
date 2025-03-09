#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

#define ETHER_ADDR_LEN 6
#define ETHER_HDR_LEN 16

struct ether_hdr{
	uchar  ether_dest_addr[ETHER_ADDR_LEN];
	uchar ether_src_addr[ETHER_ADDR_LEN];
	ushort ether_type;
};

struct ip_hdr{
uchar ip_version_and_header_length;
	uchar ip_tos;
	ushort ip_len;
	ushort ip_id;
	ushort ip_frag_offset;
	uchar ip_ttl;
	uchar ip_type;
	ushort ip_checksum;
	uint ip_src_addr;
	uint ip_dest_addr;
};

struct tcp_hdr{
	ushort tcp_src_port;
	ushort tcp_dest_port;
	uint tcp_seq;
	uint tcp_ack;
	uchar reserved:4;
	uchar tcp_offset:4;
	
	uchar tcp_flags;
#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PUSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
	ushort tcp_window;
	ushort tcp_checksum;
	ushort tcp_urgent;
};
	
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
