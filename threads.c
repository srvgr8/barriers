//syntax pthread_create(address of variable, attributes, address of function, arugments)
//pthread_create(&a,attributes,fun(),args)

#include <stdlib.h>
#include<stdio.h>
#include <pthread.h>
int n;
void *show(void *arg) //function declaration
{	
	n = atoi(arg);
	if (n%2 ==0 )
	{
		printf("even\n");
	}
	else
	{
		printf("odd");
	}
}
int main()
{	char *m = "5";
	pthread_t tid;
	pthread_create(&tid,NULL,&show,m);//here the last var 'm' is the argument for show function and is same as show(m)
	pthread_join(tid,NULL);
	printf("my thread\n");
	return 0;
}