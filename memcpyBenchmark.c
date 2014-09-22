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
void *block_Byte_random();
void *block_KByte_random();
void *block_MByte_random();

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
		printf("\nEnter the Block Size:\n1.Sequential Byte Operation\n2.Random Byte Operation \n3.Sequential KiloByte Operation\n4.Random KiloByte Operation\n5.Sequential MegaByte Operation\n6.Random MegaByte Operation\n7.Exit \nEnter your choice: ");

		scanf("%d",&ch);
		if(ch>=7)
		{
			exit(0);
		}
		printf("\nEnter the number of threads(1/2) :\n");
		scanf("%d",&nthread);
		switch (ch)
		{
			case 1: //Sequential Memroy Read+Write
			printf("\nByte read+write for %d thread",nthread);
			printf("\n\n..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Byte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE/(double)((latency)*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
			break;

			case 2:
			// Random Memroy Read+Write
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Byte_random,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE/(double)((latency)*1000));
			printf("THROUGHPUT:%f MB/sec\n",throughput);


			break;

			case 3: //Sequential Memroy Read+Write
			printf("\nKiloByte read+write for %d thread ",nthread);
			printf("\n\n..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Kbyte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE_KB/(double)((latency)*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
			break;

			case 4:
			//Random Memroy Read+Write
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_KByte_random,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE_KB/(double)((latency)*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
	
			break;

			case 5: //Sequential Memroy Read+Write
			printf("\nMegaByte read+write for %d thread \n",nthread);
			printf("..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Mbyte,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE_MB/(double)((latency)*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
			break;

			case 6:
			//Random Memory Read+Write
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_MByte_random,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
			printf("LATENCY : %f ms\n",latency);
			throughput=(BLOCK_SIZE_MB/(double)((latency)*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
	
			break;

			case 7: exit(0);
			break;
			default:printf("\nPlease enter a valid option..\n");	
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

	free(mem_write);
}

void *block_Byte_random()
{
	
	int i,r;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE));
	
//	srand((unsigned)&mem_write);

	for(i=0;i<BLOCK_SIZE;i++)
	{
		r = rand()%1000000;
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+r);
	}

	free(mem_write);
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

	free(mem_write);

}

void *block_KByte_random()
{
	
	int i,r;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_KB));

	for(i=0;i<BLOCK_SIZE_KB;i++)
	{
		r = rand()%10;	
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+r);
	}

	free(mem_write);
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

	free(mem_write);

}

void *block_MByte_random()
{
	
	int i,r;
	int len;
	double a=5;
	char mem = 'C';	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_MB));

	for(i=0;i<BLOCK_SIZE_MB;i++)
	{
		r = rand()%10;	
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+r);
	}

	free(mem_write);
}

