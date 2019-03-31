#include<pthread.h>
#include <stdio.h>
int shared = 1;
pthread_mutex_t l;//mutex lock
void *fun1()
{
	int x;
	pthread_mutex_lock(&l);//when any thread has aquired the lock to share variable the other thread is not able to acquire the 
	x=shared;				//locks thus it is not able to read the inconsistent value of shared value of shared variable so
	x++;					//only one thread is in its critical section at any given time.
	shared = x;
	pthread_mutex_unlock(&l);

}

void *fun2()
{
	int y;
	pthread_mutex_lock(&l);
	y=shared;
	y--;
	shared = y;
	pthread_mutex_unlock(&l);

}



int main()
{
	pthread_mutex_init(&l,NULL);//initialising the mutex lock
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,&fun1,NULL);
	pthread_create(&thread2,NULL,&fun2,NULL);
	pthread_join(thread1,NULL);
	printf("%d\n one", shared);
	pthread_join(thread2,NULL);
	printf("%d\n two", shared);
}