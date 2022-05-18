//chat server
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define SER_PORT 8008
using namespace std;
int main()
{
	int a,sersock,newsock,n;
	char str[250],str2[250];
	struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SER_PORT);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if((sersock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		cout<<"\n socket";
		exit(0);
	}
	if(bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr))<0)
	{
		cout<<"\nBIND";
		exit(0);
	}
	if(listen(sersock,1)<0)
	{
		cout<<"\n LISTEN";
	}
	if((newsock=accept(sersock,(struct sockaddr *)&cliinfo,&csize))<0)
	{
		cout<<"\n ACCEPT";
		exit(0);
	}
	//else
	//printf("\n now connected to %s\n",inet_ntoa(cliinfo.sin_addr));
	read(newsock,str,sizeof(str));
	do
	{
		cout<<"\n client msg: "<<str;
		cout<<"\n server msg: ";
		cin>>str2;
		write(newsock,str2,sizeof(str2));
		listen(newsock,1);
		read(newsock,str,sizeof(str));
		n=strcmp(str,"BYE");
		a=strcmp(str2,"BYE");
	}
	while(n!=0||a!=0);
	close(newsock);
	close(sersock);
	return 0;
}
