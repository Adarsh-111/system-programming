//Program to implement FIFO
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#define MAX 256
using namespace std;
int main()
{
        char fifoname[] = "fifotest";
        int fifofd,ret,bye=1;
        char readbuff[MAX];
        char writebuff[MAX];
        mkfifo(fifoname,0666);//creating FIFO for read write

        while(bye)//opening FIFO, reading FIFO, writing FIFO,closing FIFO
        {
                fifofd = open(fifoname,O_WRONLY);// process 1 read and process 2 write
                memset(writebuff,0,MAX);
                write(1,"Enter your Message:",20);
                ret = read(0,writebuff,MAX);
        //      writebuff[ret+1] = '\0';
                write(fifofd,writebuff,ret);
                close(fifofd);

                bye = strcmp("Bye\n",writebuff);
        //      cout << bye <<endl;

                if (bye)
                {
                        fifofd = open(fifoname,O_RDONLY);// process 1 write and process 2 read
                        ret = read(fifofd,readbuff,MAX);
                        write(1,"Message from Friend:",20);
                        write(1,readbuff,ret);
                        write(1,"\n",1);
                        close(fifofd);
                }
        }
}
