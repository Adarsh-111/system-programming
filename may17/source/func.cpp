//This function creates socket, shared memory TCP server function
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
using namespace std;
key_t create_key()
{
	key_t key;
	key = ftok("../data/shmfile",65);
	return key;
}

void createShm(){
        key_t key = create_key();
        int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("error creating shared memory");
                exit(EXIT_FAILURE);
        }
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
        *no_of_connections = 0;
}
void destroyShm(){
        key_t key = create_key();
        int id = shmget(key,1,0666);
        shmctl(id,IPC_RMID,0);
}
short writetoShm(){
        key_t key = create_key();
        int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("Error Accessing Shared Memory");
                exit(EXIT_FAILURE);
        }
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
        *no_of_connections += 1;
        return *no_of_connections;
}
int createSocket(const char* ip,int port){
    //We use this block for creating socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror( "socket error");
        return -1;
    }
    cout << "socket creation successfully" << endl;

    //This is to create server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //This is binding with the socket
    int ret = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0){
        perror ( "The bind is not successful " );
        return -1;
    }
    cout << "bind successfully" << endl;

    //This is to check the listening for client
    ret = listen(sock, 5);
    if(ret < 0){
        cout << "listen error" << endl;
        return -1;
    }
    cout << "listening on port "<< port << endl;
    return sock;
}
