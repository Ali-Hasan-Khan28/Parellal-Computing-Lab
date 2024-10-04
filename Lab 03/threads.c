#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* print_thread_id(void* arg)
{
	int thread_id = (int)(long)arg;
	printf("Hello from thread %d!\n",thread_id);
	pthread_exit(NULL);
}

int main()
{
	int num_thread = 3;
	pthread_t threads[num_thread];

	for (int i=0; i<num_thread;i++)
	{
		printf("Spawning thread %d\n",i);
		pthread_create(&threads[i],NULL, print_thread_id,(void*)(long)i);
	}

	for (int i=0;i<num_thread;i++)
	{
		pthread_join(threads[i],NULL);
	}

	printf("All threads have completed their execution.\n");
	return 0;
}