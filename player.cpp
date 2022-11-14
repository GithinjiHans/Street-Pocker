#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main(int argc,char** argv){
    if(argc < 3){
        std::cout << "Usage: ./client <name> <cards>" << std::endl;
        return 0;
    }
    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(sock == -1){
        std::cout << "Error creating socket" << std::endl;
        return 1;
    }
    std::cout << "Socket created" << std::endl;
    sockaddr_in6 client;
    client.sin6_family = AF_INET6;
    client.sin6_port = htons(8000);
    client.sin6_addr = in6addr_any;
    if(connect(sock, (sockaddr*)&client, sizeof(client)) < 0){
        std::cout << "Error connecting to server" << std::endl;
        return 1;
    }
    std::cout << "Connected to server" << std::endl;
    char buf[1024];
    strcpy(buf, argv[1]);
    strcat(buf, " ");
    strcat(buf, argv[2]);
    send(sock, buf, strlen(buf), 0);
    memset(buf, 0, 1024);
    recv(sock, buf, 1024, 0);
    std::cout << buf << std::endl;
    std::cout << "Sent data to server" << std::endl;
}