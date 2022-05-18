//Demonstrate race condition
#include <iostrea>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
int balance = 0;
void computebal( void *arg ){
	int b,c;
	b=balance;
	for( int i = 0; i<5000; i++){
		c=5000* 1234;
	}
	b+=10;
	balance = b;
}

int main(){
	int i;
	pthread_t thread_id[200];
	cout << "Balance Before Thread: " << balance <<endl;
	for(int i=0;i < 200;i++){
		pthread_create(&thread_id[i],NULL,computebal,NULL);
	}
	for(int i=0;i < 200;i++){
		pthread_create(thread_id[i],NULL,computebal,NULL);
	}

