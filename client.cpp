#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<iostream>
#include<string.h>
#include<unistd.h>

using namespace std;

int main(){
  string destination;
  unsigned short port = 7788;

  int dst_socket;
  struct sockaddr_in dst_addr;

  //cout << "Connect to ?:(name or IP address)" << endl;
  //cin >> destination;

  destination = "192.168.11.5";

  memset(&dst_addr, 0, sizeof(dst_addr));
  dst_addr.sin_port = htons(port);
  dst_addr.sin_family = AF_INET;
  dst_addr.sin_addr.s_addr = inet_addr(destination.c_str());

  dst_socket = socket(AF_INET, SOCK_STREAM, 0);
  cout << "Trying to connect to " << destination << endl;
  connect(dst_socket, (struct sockaddr *)&dst_addr, sizeof(dst_addr));

  for(int i = 0; i < 10; ++i ){
    string buffer;
    cout << "you :";
    cin >> buffer;
    send(dst_socket, buffer.c_str(), strlen(buffer.c_str())+1, 0);
  }

  close(dst_socket);

  return 0;
}
