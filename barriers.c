#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>


pthread_mutex_t lock;
pthread_cond_t  finish_cond;
int barrier = 0;
int invoke_barrier = 0;
int barrier_size;
int counter=0;
int thread_count;

void barrier_init(int n_threads)
{
    if ( thread_count < barrier_size )
        { 
            barrier = thread_count;
            return;
        }
        barrier = n_threads;
}
int decr()
{
    if (barrier == 0) 
    {
        return 0;
    }

    if(pthread_mutex_lock(&lock) != 0)
    {
        perror("Failed to acquire lock. Exiting now.");
        return -1;
    }

    barrier--;

    if(pthread_mutex_unlock(&lock) != 0)
    {
        perror("Failed to unlock.");
        return -1;
    }

    return 0;
}

int wait_barrier()
{
    if(decr() < 0)
    {
        return -1;
    }

    while (barrier)
    {
        if(pthread_mutex_lock(&lock) != 0)
        {
            perror("\n Error while locking mutex");
            return -1;
        }

        if(pthread_cond_wait(&finish_cond, &lock) != 0)
        {
            perror("\n Error in cond wait.");
            return -1;
        }
    }

    if(0 == barrier)
    {
        if(pthread_mutex_unlock(&lock) != 0)
        {
            perror("\n Error while locking mutex");
            return -1;
        }
        if(pthread_cond_signal(&finish_cond) != 0)
        {
            perror("\n Error while signaling.");
            return -1;
        }
    }

    return 0;
}



void * barrier_point(void *num_thread)
{

     int random = rand() % 8;

     printf("\nThread %d \nPerforming init task of %d sec\n",++counter,r);
     sleep(r);

     wait_barrier();
     if (barrier_size!=0)
     {
       if ((thread_count - (invoke_barrier++) ) % barrier_size == 0) {
         printf("\nBarrier Released\n");
       }
       printf("\nThreads after the barrier\n");

     }

     return  NULL;
}

int main()
{

    printf("Enter Barrier Size\n");
    scanf("%d", &barrier_size);

    printf("Enter number of thread\n");
    scanf("%d", &thread_count);


    if (barrier_size>=0 && thread_count>=0) {
        pthread_t tid[thread_count];

        barrier_init(barrier_size);

        for(int i =0; i < thread_count; i++)
        {
            pthread_create(&(tid[i]), NULL, &barrier_point, &thread_count);
        }


        for(int j = 0; j < thread_count; j++)
        {
            pthread_join(tid[j], NULL);
        }
    }

    else{
      printf("Invalid Input.\n");
      main();
    }

    return 0;
}