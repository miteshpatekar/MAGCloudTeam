#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024

void *block_Byte();
void *block_Kbyte();
void *block_Mbyte();

int main()
{

	struct timeval start, end;
	struct timezone tzp;

	double latency,throughput;
	printf("\n........Program to find Memory Benchmark.......\n");
	pthread_t th[10];// array of threads
	int i;
	int ch,nthread;
	while(1)
	{
		printf("\n\nEnter the Block Size:\n1.BYTE\n2.KILOBYTE\n3.MEGABYTE\n4.EXIT : \n");


		scanf("%d",&ch);
		if(ch==4)
		{
			exit(0);
		}
		printf("\n\nEnter the number of threads(1/2) :\n");
		scanf("%d",&nthread);
		switch (ch)
		{
			case 1: //Sequential Memroy Read+Write
			printf("\nByte read+write for %d thread",nthread);
			printf("\n\nSequential Read+Write");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Byte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("\nLatency : %f ms",latency);
			throughput=(BLOCK_SIZE/(double)((latency)*1000));
			printf("\nThroughtput:%f MB/sec",throughput);
			break;

			case 2: //Sequential Memroy Read+Write
			printf("\nKiloByte read+write for %d thread ",nthread);
			printf("\n\nSequential Read+Write");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Kbyte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("\nLatency : %f ms\n",latency);
			throughput=(BLOCK_SIZE_KB/(double)((latency)*1000));
			printf("\nThroughtput:%f MB/sec\n",throughput);
			break;

			case 3: //Sequential Memroy Read+Write
			printf("\MegaByte read+write for %d thread ",nthread);
			printf("\n\nSequential Read+Write");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Mbyte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("\nLatency : %f ms\n",latency);
			throughput=(BLOCK_SIZE_KB/(double)((latency)*1000));
			printf("\nThroughtput:%f MB/sec\n",throughput);
			break;

			case 4: exit(0);
			break;
			default:printf("/nPlease enter a valid option..\n");	
		}
	}
}

void *block_Byte()
{
	
	int i;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE));

	for(i=0;i<BLOCK_SIZE;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
	}

}

void *block_Kbyte()
{

	int i;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_KB));
	
	for(i=0;i<BLOCK_SIZE_KB;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
	}
}

void *block_Mbyte()
{
	int i;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_MB));

	for(i=0;i<BLOCK_SIZE_MB;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
	}

}
