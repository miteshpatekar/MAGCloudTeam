#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>
#include<string.h>

// thread function to calculate Flops
void *threadFunctionFlop(void *arg)
{
	int i;
	double a=5;
	//  convert string argument to long
	long iterations=strtol((char*)arg,NULL,0);
	printf("\nThread is  %lu",iterations);
	for(i = 0; i < iterations; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

// thread function to calculate Iops
void *threadFunctionIops(void *arg)
{
	int i;
	int a=5;
	//  convert string argument to long
	long iterations=strtol((char*)arg,NULL,0);
	printf("\nThread is  %lu",iterations);
	for(i = 0; i < iterations; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

void flops(int numberOfThreads)
{
	int i;
    	long double a=5;
	struct timeval start, end;
    	struct timezone tzp;
    	pthread_t th[10];// array of threads

    	long iterations=10000000/numberOfThreads;
	char iterationStr[20];
	snprintf(iterationStr, 20, "%lu",iterations);
	
	printf("\nProgram to find FLOPS");
	gettimeofday(&start, &tzp);//  calculate start time
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlop,iterationStr);
		pthread_join(th[i], NULL);
	}
    	gettimeofday(&end, &tzp); // calculate end time
    
    	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;//  time in milliseconds
    	printf("\nTime: %f ms\n",timeMs);
    	double Flops=(10000000)/(double)(timeMs/1000);
    	double gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: Flops * 10raised to (-9).
    	
    	printf("GFLOPS : %f\n",gFlops);
}

void iops(int numberOfThreads)
{
	int i;
    	int a=5;
	struct timeval start, end;
    	struct timezone tzp;
    	pthread_t th[10];// array of threads

    	long iterations=10000000/numberOfThreads;
	char iterationStr[20];
	snprintf(iterationStr, 20, "%lu",iterations);
	
	printf("\nProgram to find IOPS");
	gettimeofday(&start, &tzp);//  calculate start time
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIops,iterationStr);
		pthread_join(th[i], NULL);
	}
    	gettimeofday(&end, &tzp);
    	
    	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nTime: %f ms\n",timeMs);
    	double Iops=(10000000)/(double)(timeMs/1000);
    	double gIops=(double)Iops/1000000000;
    	
    	printf("GIOPS : %f\n",gIops);
}

int main(int argc, char *argv[])
{
	printf("Number of threads %s", argv[1]);
	int numberOfThreads=atoi(argv[1]);
    	flops(numberOfThreads);
    	iops(numberOfThreads);
    	return 0;
}
