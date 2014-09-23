#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1000

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
	clock_t start_t, end_t, total_t=0,start_t1, end_t1,total_t1=0;
	double latency,throughput;
	printf("\n........Program to find Memory Benchmark.......\n");
	pthread_t th[10];// array of threads
	int i;
	int ch,nthread;
	while(1)
	{
		printf("\nEnter the Block Size:\n1.BYTE\n2.KILOBYTE\n3.MEGABYTE\n4.Exit\n");

		scanf("%d",&ch);
		if(ch>=4)
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
			printf("\n\n..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
		
			for(i=0;i<nthread;i++)
			{
			
				start_t = clock();	
				pthread_create(&th[i],NULL,block_Byte,NULL);
				pthread_join(th[i], NULL);
				total_t += clock() - start_t;
			}
			
			double lat = (double)(total_t*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for sequential 1 Byte : %f\n", lat);
			total_t = 0;
		
			throughput=(BLOCK_SIZE/(double)((lat)*100*1000));
			printf("THROUGHPUT for seq 1 Byte : %f MB/sec\n",throughput);
			lat =0;
			
			// Random Memroy Read+Write
			
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			for(i=0;i<nthread;i++)
			{
				start_t1 = clock();
				pthread_create(&th[i],NULL,block_Byte_random,NULL);
				pthread_join(th[i], NULL);
				total_t1 += clock() - start_t1;
			}
		
			double lat1 = (double)(total_t1*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for random 1 Byte :%f\n", lat1);
		
			throughput=(BLOCK_SIZE/(double)((lat1)*100*1000));
			printf("THROUGHPUT for 1 byte random : %f MB/sec\n",throughput);
			
			break;

			case 2: 
			
			//Sequential Memroy Read+Write for KILOBYTE block
			
			printf("\nKiloByte read+write for %d thread ",nthread);
			printf("\n\n..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
			
			for(i=0;i<nthread;i++)
			{
				start_t = clock();
				pthread_create(&th[i],NULL,block_Kbyte,NULL);
				pthread_join(th[i], NULL);
				total_t += clock() - start_t;
			}
			
			double lat = (double)(total_t*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for sequential 1 Byte : %f\n", lat);
			total_t = 0;
			
			throughput=(BLOCK_SIZE_KB/(double)((lat)*100*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
			
			//Random Memroy Read+Write for KILOBYTE block
			
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			
			for(i=0;i<nthread;i++)
			{
				start_t1 = clock();
				pthread_create(&th[i],NULL,block_KByte_random,NULL);
				pthread_join(th[i], NULL);
				total_t1 += clock() - start_t1;
			}
			
			double lat1 = (double)(total_t1*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for sequential 1 Byte : %f\n", lat);
			total_t = 0;
			
			throughput=(BLOCK_SIZE_KB/(double)((lat1)*100*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
	
			break;

			case 3: 
			
			//Sequential Memroy Read+Write
			
			printf("\nMegaByte read+write for %d thread \n",nthread);
			printf("..Sequential Read+Write..\n");
			printf("-------------------------------------\n");
			
			for(i=0;i<nthread;i++)
			{
				start_t = clock();
				pthread_create(&th[i],NULL,block_Mbyte,NULL);
				pthread_join(th[i], NULL);
				total_t += clock() - start_t;
			}
			
			double lat = (double)(total_t*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for sequential 1 Byte : %f\n", lat);
			total_t = 0;
			
			throughput=(BLOCK_SIZE_MB/(double)((lat)*100*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
			
			//Random Memory Read+Write
			
			printf("..Random read+write..\n");
			printf("-------------------------------------\n");
			
			for(i=0;i<nthread;i++)
			{
				start_t1 = clock();
				pthread_create(&th[i],NULL,block_MByte_random,NULL);
				pthread_join(th[i], NULL);
				total_t1 += clock() - start_t1;
			}
			
			double lat1 = (double)(total_t1*1000)/(nthread*CLOCKS_PER_SEC);
			printf("Latency for sequential 1 Byte : %f\n", lat);
			total_t = 0;
			
			throughput=(BLOCK_SIZE_MB/(double)((lat1)*100*1000));
			printf("THROUGHPUT : %f MB/sec\n",throughput);
	
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
	char *mem = malloc(100*sizeof(*mem));
	for(k=0;k<100;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*sizeof(*mem_write));
		
	for(i=0;i<100;i++)
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
	
	char *mem = malloc(100*sizeof(*mem));
	for(k=0;k<100;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*sizeof(*mem_write));
		
	for(i=0;i<100;i++)
	{
		r = rand()%100;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE);
	}
}

void *block_Kbyte()
{

	int i;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(100*1024*sizeof(*mem));
	
	for(k=0;k<100*1024;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*1024*sizeof(*mem_write));
		
	for(i=0;i<100;i++)
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
	char *mem = malloc(100*1024*sizeof(*mem));
	for(k=0;k<100*1024;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*1024*sizeof(*mem_write));
		
	for(i=0;i<100;i++)
	{
		r = rand()%100*1024;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE_KB);	
	}
}

void *block_Mbyte()
{
	int i;
	int len;
	double a=5;
	long k= 0;
	char *mem = malloc(100*1024*1024*sizeof(*mem));
	for(k=0;k<1024*1024*100;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*1024*1024*sizeof(*mem_write));
		
	for(i=0;i<1024*1024*100;i++)
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
	char *mem = malloc(100*1024*1024*sizeof(*mem));
	for(k=0;k<1024*1024*100;k++)
	{
		mem[k]='c';
	}	
	char *mem_write=malloc(100*1024*1024*sizeof(*mem_write));

	for(i=0;i<100;i++)
	{
		r = rand()%100*1024*1024;	
		memcpy(mem_write + r,&mem +r,BLOCK_SIZE_MB);
	}
}

