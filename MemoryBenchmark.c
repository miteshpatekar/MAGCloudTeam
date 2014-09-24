#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024

#define BITERATIONS 1000000
#define KBITERATIONS 100000
#define MBITERATIONS 100

void *block_Byte();
void *block_Kbyte();
void *block_Mbyte();
void *block_Byte_random();
void *block_KByte_random();
void *block_MByte_random();

int main()
{

	clock_t start_t, end_t, total_t=0,start_t1, end_t1,total_t1=0;
	double latency,throughput,timeDiff;
	double lat;
	printf("\n........Program to find Memory Benchmark.......");
	pthread_t th[10];// array of threads
	int i;
	int ch,nthread;
	while(1)
	{
		printf("\n\nEnter the Block Size:\n1.BYTE\n2.KILOBYTE\n3.MEGABYTE\n4.Exit\n");

		scanf("%d",&ch);
		if(ch==4)
		{
			exit(0);
		}
		printf("\nEnter the number of threads(1/2) :\n");
		scanf("%d",&nthread);
		switch (ch)
		{
			case 1: 
			
			//Sequential Memroy Read+Write
			
			printf("\nByte read+write for %d thread",nthread);
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
		
			start_t = clock();
			for(i=0;i<nthread;i++)
			{	
				pthread_create(&th[i],NULL,block_Byte,NULL);
				pthread_join(th[i], NULL);
			}
			
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BITERATIONS/(double)(latency*BLOCK_SIZE_MB));
    			printf("\nThroughtput:%f MB/s",throughput*1000);
			
			
			// Random Memroy Read+Write
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start_t=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Byte_random,NULL);
				pthread_join(th[i], NULL);
			}
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BITERATIONS/(double)(latency*BLOCK_SIZE_MB));
    			printf("\nThroughtput:%f MB/s",throughput*1000);
			break;
			
			case 2: 
			//Sequential Memroy Read+Write for KILOBYTE block
			
			printf("\n\nKiloByte read+write for %d thread ",nthread);
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
			start_t = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Kbyte,NULL);
				pthread_join(th[i], NULL);
			}
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KBITERATIONS/(double)(latency*BLOCK_SIZE_KB));
    			printf("\nThroughtput:%f MB/s",throughput*1000);
			
	
			//Random Memroy Read+Write for KILOBYTE block
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start_t = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_KByte_random,NULL);
				pthread_join(th[i], NULL);
			}
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KBITERATIONS/(double)(latency*BLOCK_SIZE_KB));
    			printf("\nThroughtput:%f MB/s",throughput*1000);
			break;

			case 3: 
			
			//Sequential Memroy Read+Write
			
			printf("\nMegaByte read+write for %d thread",nthread);
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
			start_t = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Mbyte,NULL);
				pthread_join(th[i], NULL);
			}
			
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MBITERATIONS/(double)(latency));
    			printf("\nThroughtput:%f MB/s",throughput*1000);			
			
			
			//Random Memory Read+Write
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start_t1 = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_MByte_random,NULL);
				pthread_join(th[i], NULL);
			}
			end_t=clock();
			timeDiff = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MBITERATIONS/(double)(latency));
    			printf("\nThroughtput:%f MB/s",throughput*1000);			
			
			break;

			case 4: exit(0);
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
	long k= 0;
	char *mem = malloc(sizeof(*mem));
	mem[0]='c';
	char *mem_write=malloc(sizeof(*mem_write));
		
	for(i=0;i<BITERATIONS;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
	}
}

void *block_Byte_random()
{
	int i,r;
	int len;
	double a=5;
	long k= 0;
	
	char *mem = malloc(sizeof(*mem));
	mem[k]='c';
		
	char *mem_write=malloc(sizeof(*mem_write));
		
	for(i=0;i<BITERATIONS;i++)
	{
		r = rand()%BLOCK_SIZE;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE);
	}
}

void *block_Kbyte()
{
	int i;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(1000*sizeof(*mem));
	for(k=0;k<1000;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(BLOCK_SIZE_KB*sizeof(*mem_write));
		
	for(i=0;i<KBITERATIONS;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE_KB);
		*(mem_write+i);
	}
}

void *block_KByte_random()
{
	int i,r;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(1000*sizeof(*mem));
	for(k=0;k<1000;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(BLOCK_SIZE_KB*sizeof(*mem_write));
		
	for(i=0;i<KBITERATIONS;i++)
	{
		r = rand()%BLOCK_SIZE_KB;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE_KB);	
	}
}

void *block_Mbyte()
{
	int i;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(1000*sizeof(*mem));
	for(k=0;k<1000;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(BLOCK_SIZE_MB*sizeof(*mem_write));
		
	for(i=0;i<MBITERATIONS;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE_MB);
		*(mem_write+i);
	}
}

void *block_MByte_random()
{	
	int i,r;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(1000*sizeof(*mem));
	for(k=0;k<1000;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(BLOCK_SIZE_MB*sizeof(*mem_write));

	for(i=0;i<MBITERATIONS;i++)
	{
		r = rand()%MBITERATIONS;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE_MB);
	}
}
