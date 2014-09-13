#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<pthread.h>
#include<semaphore.h>

/* This is our thread function.  It is like main(), but for a thread */
void *threadFunc1(void *arg)
{
	char *str;
	int i = 0;
	double a=5;
	//str=(char*)arg;
	printf("\nThread 1 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}

	return NULL;
}

void *threadFunc2(void *arg)
{
	char *str;
	int i = 0;
	double a=5;
	//str=(char*)arg;

	printf("\nThread 2 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}

	return NULL;
}

void *threadFunc3(void *arg)
{
	char *str;
	int i = 0;
	double a=5;
	//str=(char*)arg;
	printf("\nThread 3 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}

	return NULL;
}

void *threadFunc4(void *arg)
{
	char *str;
	int i = 0;
	double a=5;
	//str=(char*)arg;
	printf("\nThread 4 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}

	return NULL;
}

void flops()
{
	int i;
    	double a=5;
	struct timeval start, end;
    	struct timezone tzp;
    	pthread_t pth1, pth2,pth3,pth4;	// this is our thread identifier
		
	printf("\nProgram to find FLOPS");
	gettimeofday(&start, &tzp);
	
	/*pthread_create(&pth1,NULL,threadFunc1,"");
	pthread_create(&pth2,NULL,threadFunc2,"");
	pthread_create(&pth3,NULL,threadFunc3,"");
	pthread_create(&pth4,NULL,threadFunc4,"");
	
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	pthread_join(pth3, NULL);
	pthread_join(pth4, NULL);
	*/
   	for(i = 0; i < 10000000; i++)
    	{
        	a=a+a;    
    	}
    	
    	gettimeofday(&end, &tzp);
 
    	printf("\nstart: %lu\n", start.tv_usec);
    	printf("end: %lu\n", end.tv_usec);
    	printf("time: %lu\n", end.tv_usec - start.tv_usec);
    	long l=(10000000)/((end.tv_usec - start.tv_usec));
    	//printf("%lu"l);
    	double lb=l/1000;
    	printf("Double %f",lb);
    	
    	printf("Floating point operations per second: %lu\n",l);
}

void iops()
{
	int i;
    	int a=5;
	struct timeval start, end;
    	struct timezone tzp;
    	pthread_t pth1, pth2,pth3,pth4;	// this is our thread identifier
	
	printf("\nProgram to find IOPS");
	gettimeofday(&start, &tzp);
	
	/*pthread_create(&pth1,NULL,threadFunc1,"");
	pthread_create(&pth2,NULL,threadFunc2,"");
	pthread_create(&pth3,NULL,threadFunc3,"");
	pthread_create(&pth4,NULL,threadFunc4,"");
	
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	pthread_join(pth3, NULL);
	pthread_join(pth4, NULL);*/
	
   	for(i = 0; i < 10000000; i++)
    	{
        	a=a+a;    
    	}
    	
	
    	gettimeofday(&end, &tzp);
 
    	printf("\nstart: %lu\n", start.tv_usec);
    	printf("end: %lu\n", end.tv_usec);
    	printf("time: %lu\n", end.tv_usec - start.tv_usec);
    	printf("Integer point operations per second: %lu\n", 10000000/(end.tv_usec - start.tv_usec));
}

int main(int argc, char *argv[])
{
    	flops();
    	//iops();
    	return 0;
}
