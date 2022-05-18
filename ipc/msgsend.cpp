//Program to send message to a message queue
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 256
using namespace std;
struct msg_buffer {
        long msg_type;
        char msg_text[MAX];
}msg;

int main()
{
        key_t key;
        int msgid;

        key = ftok("keyfile",65); //create a key(filename ,)
        msgid = msgget(key, 0666 | IPC_CREAT);
        write(1,"Print Message to Store: ",24);
        read(0,msg.msg_text,MAX);
        msg.msg_type = 1;
        msgsnd(msgid,&msg,sizeof(msg),0);
        cout << "Data Sent to Queue: "<< msg.msg_text << endl;
}
