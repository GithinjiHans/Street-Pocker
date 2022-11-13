#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock == -1){
        std::cout << "Error creating socket" << std::endl;
        return 1;
    }
    std::cout << "Socket created" << std::endl;
//    connect to remote server
    sockaddr_in6 server;
    server.sin6_family = AF_INET6;
    server.sin6_port = htons(5410);
    inet_pton(AF_INET6, "::1", &server.sin6_addr);
    // send a datagram
    char buf[1024];
    std::string userInput;
    do{
        std::cout << "> ";
        std::getline(std::cin, userInput);
        if(userInput.size() > 0){
            int sendRes = sendto(sock, userInput.c_str(), userInput.size() + 1, 0, (sockaddr*)&server, sizeof(server));
            if(sendRes == -1){
                std::cout << "Could not send to server! Whoops!\r" << std::endl;
                continue;
            }
            // wait for response
        }
    }while(userInput.size() > 0);
    // close the socket
    close(sock);
}