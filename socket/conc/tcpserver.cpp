//The program to create a test TCP server
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8008
#define MAX 256
using namespace std;


int main() {
        struct sockaddr_in servaddr, cliaddr;
        char smsg[MAX];
        char cmsg[MAX];
        int sockfd,mlen,slen,connfd,ret,t1,t2,n1=1,n2=1;//Initialising sock filedescriptor, message length, structure length
        socklen_t clen;
        pid_t client_pid;

        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);


        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);


        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd < 0){
                fputs("Error: Can't create socket",stderr);
                exit(EXIT_FAILURE);
        }


        ret = bind(sockfd,(const struct sockaddr *)&servaddr,slen);
        if (ret < 0){
                fputs("Error: Can't bind socket",stderr);
                exit(EXIT_FAILURE);
        }


        ret = listen(sockfd,5);
        if (ret < 0){
                fputs("Error: Can't LISTEN socket",stderr);
                exit(EXIT_FAILURE);
        }

        while(1)
       	{
        	connfd=accept(sockfd,(struct sockaddr *) &cliaddr, &clen);
        	if (connfd < 0)
		{
                	fputs("Error: Can't accept the connection",stderr);
                	exit(EXIT_FAILURE);
        	}



        	client_pid = fork();

        	if (client_pid == 0) 
		{
                	close(sockfd);
			while(n1 != 0 && n2 != 0)
			{
                		mlen=read(connfd,cmsg,MAX);
                		write(1,"Message from the client - ",27);
                		write(1,cmsg, strlen(cmsg));
                		write(1,"Give message for client- ",26);
                		mlen = read(0,smsg,MAX);
                		mlen=write(connfd,smsg,strlen(smsg));
                		cout << "Message sent from the server" << endl;
			//t1=strlen(cmsg);
			//t2=strlen(smsg);
			//cmsg[t1]='\0';
			//smsg[t2]='\0';
                		close(connfd);
				n1=strcmp(cmsg,"BYE\n");
                        	n2=strcmp(smsg,"BYE\n");
				cout<<"n1"<<n1;
				cout<<"n2"<<n2;
                	//exit(EXIT_SUCCESS);
			//if(n1==0)
			}
        	}
                	close(connfd);
        }
        //while(n1!=0);
	close(sockfd);
	return 0;
}
