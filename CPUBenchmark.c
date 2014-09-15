#include<stdio.h>
#include<sys/time.h>
#include<pthread.h>

void *threadFunction1(void *arg)
{
	int i;
	double a=5;
	printf("\nThread 1 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

void *threadFunction2(void *arg)
{
	int i = 0;
	double a=5;
	printf("\nThread 2 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

void *threadFunction3(void *arg)
{
	int i = 0;
	double a=5;
	printf("\nThread 3 ");
	for(i = 0; i < 2500000; i++)
    	{
        	a=a+a;    
    	}
	return NULL;
}

void *threadFunction4(void *arg)
{
	int i = 0;
	double a=5;
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
    	pthread_t pth1, pth2,pth3,pth4;
		
	printf("\nProgram to find FLOPS");
	gettimeofday(&start, &tzp);
	
	pthread_create(&pth1,NULL,threadFunction1,"");
	pthread_create(&pth2,NULL,threadFunction2,"");
	pthread_create(&pth3,NULL,threadFunction3,"");
	pthread_create(&pth4,NULL,threadFunction4,"");
	
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	pthread_join(pth3, NULL);
	pthread_join(pth4, NULL);
	
   	/*for(i = 0; i < 10000000; i++)
    	{
        	a=a+a;    
    	}*/
    	
    	gettimeofday(&end, &tzp);
    	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nTime: %f ms\n",timeMs);
    	double Flops=(10000000)/(double)(timeMs/1000);
    	double gFlops=(double)Flops/1000000000;
    	
    	printf("GFLOPS : %f\n",gFlops);
}

void iops()
{
	int i;
    	int a=5;
	struct timeval start, end;
    	struct timezone tzp;
    	pthread_t pth1, pth2,pth3,pth4;
	
	printf("\nProgram to find IOPS");
	gettimeofday(&start, &tzp);
	
	pthread_create(&pth1,NULL,threadFunction1,"");
	pthread_create(&pth2,NULL,threadFunction2,"");
	pthread_create(&pth3,NULL,threadFunction3,"");
	pthread_create(&pth4,NULL,threadFunction4,"");
	
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	pthread_join(pth3, NULL);
	pthread_join(pth4, NULL);
	
   	/*for(i = 0; i < 10000000; i++)
    	{
        	a=a+a;    
    	}*/
    	gettimeofday(&end, &tzp);
    	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nTime: %f ms\n",timeMs);
    	double Iops=(10000000)/(double)(timeMs/1000);
    	double gIops=(double)Iops/1000000000;
    	
    	printf("GIOPS : %f\n",gIops);
}

int main(int argc, char *argv[])
{
    	flops();
    	iops();
    	return 0;
}
