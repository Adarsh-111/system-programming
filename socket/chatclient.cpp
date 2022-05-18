//chatclient program

#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#define ADDSERV "127.0.0.1"
#define SER_PORT 8008
#define MAX 256
using namespace std;
int main()
{
	int a,clisock;
	char str[MAX],str2[MAX];
	struct sockaddr_in cliaddr;
	cliaddr.sin_port=htons(SER_PORT);
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_addr.s_addr=inet_addr(ADDSERV);
	clisock=socket(AF_INET,SOCK_STREAM,0);
	memset(str,0,MAX);
	memset(str2,0,MAX);
	if(clisock<0)
	{
		perror("\n SOCKET");
		exit(0);
	}
	if(connect(clisock,(struct sockaddr *)&cliaddr,sizeof(cliaddr))<0)
	{
		perror("\n CONNECT");
		exit(0);
	}
	cout<<"\nCLIENT";
	cin>>str;
	if(write(clisock,str,sizeof(str))<0)
	{
		cout<<"\n data could not be sent";
	}
	do
	{
		listen(clisock,1);
		read(clisock,str2,sizeof(str2));
		cout<<"\nserver msg: "<<str2;
		cout<<"\nclient msg:";
		cin>>str;
		a=strcmp(str2,"BYE");
		write(clisock,str2,sizeof(str2));
	}
	while(a!=0);
	close(clisock);
	return 0;
}
