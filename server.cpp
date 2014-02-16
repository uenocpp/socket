#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

const int BUF_SIZE = 1024;

int main(){
  unsigned short port = 7788;
  int src_socket;
  int dst_socket;

  struct sockaddr_in src_addr;
  struct sockaddr_in dst_addr;
  unsigned int dst_addr_size = sizeof(sockaddr_in);

  int numrcv;
  char buffer[BUF_SIZE];
  int status;

  memset(&src_addr, 0, sizeof(src_addr));
  src_addr.sin_port = htons(port);
  src_addr.sin_family = AF_INET;
  src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  src_socket = socket(AF_INET, SOCK_STREAM, 0);

  bind(src_socket, (struct sockaddr *)&src_addr, sizeof(src_addr));

  listen(src_socket, 1);

  printf("Waiting for connection...\n");
  dst_socket = accept(src_socket, (struct sockaddr *)&dst_addr, &dst_addr_size);
  printf("Connetced from %s\n", inet_ntoa(dst_addr.sin_addr));

  while(1){
    numrcv = recv(dst_socket, buffer, BUF_SIZE, 0);
    if( numrcv == 0 || numrcv == -1 ){
      status = close(dst_socket);
      break;
    }
    printf("received: %s\n", buffer);
  }

  return 0;
}
