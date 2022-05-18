//This program creates a TCP client and connects with TCP server
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
using namespace std;
int main(int argc,char* argv[]){
        const char* port = "8008";
        int portno = atoi(port);
        int socketid = socket(AF_INET,SOCK_STREAM,0);
        if(socketid==-1){
                std::cout<<"Socket creation failed"<<std::endl;
                return -1;
        }
        cout << "Socket created successfully" << std::endl;

        struct sockaddr_in serveraddr;

        memset(&serveraddr,0,sizeof(serveraddr));

        serveraddr.sin_family=AF_INET;
        serveraddr.sin_port=htons(portno);
        serveraddr.sin_addr.s_addr= inet_addr("127.0.0.1");

        int connect_status = connect(socketid,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
        if(connect_status==-1){
                std::cout<<"Connection failed"<<std::endl;
                return -1;
        }
        cout << "Connection successful" << std::endl;
        cout << "Enter the message to be sent to the server : ";
        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
                std::cout<<"Message sending failed"<<std::endl;
                return -1;
        }
        cout << "Message sent successfully" << std::endl;

        while(1){

        char buffer[256];
        memset(buffer,0,sizeof(buffer));

        int len=sizeof(serveraddr);
        ssize_t receive_status = recv(socketid,buffer,256,0);
        if(receive_status==-1){
                cout<<"Message receiving failed"<<endl;
                return -1;
        }
        else if(receive_status==0){
                cout<<"Server closed the connection"<<endl;
                break;
        }
        cout << "Message received successfully" << endl;

        cout<<"Message received : "<<buffer<<endl;

        if(strcmp(buffer,"Bye")==0)
        break;

        cout << "Enter the message to be sent to the server : ";
        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
                perror("Message sending failed");
                return -1;
        }
        cout << "Message sent successfully" << endl;
        if(strcmp(message,"Bye")==0)
        break;
        }
        close(socketid);
}
