//The main Server Program
#include <iostream>
#include "../include/header.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
using namespace std;
int main(int argc, char* argv[]){
        createShm();
        int sock = createSocket("0.0.0.0",8008);
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        while(1){
        int client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if(client_sock < 0){
            perror( "accept error") ;
            return -1;
        }
        cout << "The client is connected Successfully to the server" << endl;
        int clientsNO = writetoShm();
        cout << "Number of clients connected to the server: " << clientsNO << endl;

        pid_t pid = fork();
        if(pid < 0){
            perror( "fork error");
            return -1;
        }
        else if(pid == 0){
            close(sock);
            char buf[1024];
            while(1){
                memset(buf, 0, sizeof(buf));
                int len = recv(client_sock, buf, sizeof(buf), 0);
                if(len < 0){
                    perror( "recv error");
                    return -1;
                }
                else if(len == 0){
                    cout << "client closed" << std::endl;
                    break;
                }
                else{
                    cout << "client send: " << buf << std::endl;
                    memset(buf,0,sizeof(buf));
                    cout << "please input the message: ";
                    cin.getline(buf,sizeof(buf));
                    send(client_sock, buf, strlen(buf), 0);
                }
            }
            close(client_sock);
            exit(0);
        }
        else{
            close(client_sock);
        }
    }
    destroyShm();
    close(sock);
}
