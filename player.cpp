#include <iostream>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

void* send_msg(void* socket){
    int sock = *((int*)socket);
    while(true){
        std::string msg;
        std::getline(std::cin, msg);
        send(sock, msg.c_str(), msg.size(), 0);
    }
}

void* recv_msg(void* socket){
    int sock = *((int*)socket);
    char buf[1024];
    memset(buf, 0, 1024);
    while(int len = recv(sock, buf, 100, 0)>0){        
        std::cout << buf << std::endl;
        memset(buf, 0, 1024);
    }
    return nullptr;
} 

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
    pthread_t thread;
    pthread_create(&thread, nullptr, send_msg,&sock);
    pthread_create(&thread, nullptr, recv_msg,&sock);
    pthread_join(thread, nullptr);
}