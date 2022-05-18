//Program to recieve message to a message queue
#include <iostream>
#include <unistd.h>
#include <string.h>
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
        msgrcv(msgid,&msg,sizeof(msg),1,0);
        cout << "Data Got from Queue: "<< msg.msg_text << endl;
        msgctl(msgid,IPC_RMID,NULL);
        return 0;
}
