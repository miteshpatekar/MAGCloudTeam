#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<pthread.h>
#include<string.h>

#define ITERATIONS 10000000

// thread function to calculate Flops
void *threadFunctionFlop(void *arg)
{
	int i;
	double a=5;
	//  convert string argument to long
	long iterations=strtol((char*)arg,NULL,0);
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
	for(i = 0; i < iterations; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

void flops(int numberOfThreads)
{
	clock_t start, end;
	double cpu_time_used;
	int i;
    	long double a=5;
    	struct timezone tzp;
    	pthread_t th[10];// array of threads

    	long iterations=ITERATIONS/numberOfThreads;
	char iterationStr[20];
	snprintf(iterationStr, 20, "%lu",iterations);
	
	printf("\nProgram to find FLOPS for %d threads",numberOfThreads);
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlop,iterationStr);
		pthread_join(th[i], NULL);
	}
    	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    	printf("\nTime: %f ms\n",cpu_time_used);
    	double Flops=(ITERATIONS)/(double)(cpu_time_used);
    	double gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: Flops * 10raised to (-9).
    	
    	printf("GFLOPS : %f\n",gFlops);
}

void iops(int numberOfThreads)
{
	clock_t start, end;
	int i;
    	int a=5;
    	double cpu_time_used;
	//struct timeval start, end;
    	struct timezone tzp;
    	pthread_t th[10];// array of threads

    	long iterations=ITERATIONS/numberOfThreads;
	char iterationStr[20];
	snprintf(iterationStr, 20, "%lu",iterations);
	
	printf("\nProgram to find IOPS for %d threads",numberOfThreads);
	start=clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIops,iterationStr);
		pthread_join(th[i], NULL);
	}
    	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    	printf("\nTime: %f ms\n",cpu_time_used);
    	double Iops=(ITERATIONS)/(double)(cpu_time_used);
    	double gIops=(double)Iops/1000000000;
    	
    	printf("GIOPS : %f\n",gIops);
}

int main()
{
	int numberOfThreads;;
	while(1)
	{
		printf("\nEnter the no of threads:(1/2/4/8) (Exit-0) : ");
		scanf("%d",&numberOfThreads);	
		if(numberOfThreads!=1 && numberOfThreads!=2 && numberOfThreads!=4 
		&& numberOfThreads!=8 && numberOfThreads!=0 )
		{
			printf("\nInvalid choice..Please enter again");
			
		}
		else if(numberOfThreads==0)
		{
			exit(0);
		}
		else
		{
			flops(numberOfThreads);
    			iops(numberOfThreads);
		}	
	}
    	
    	return 0;
}
