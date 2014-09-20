#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024

int main()
{
	
	printf("Memory Benchmarking \n");
	block_Byte();
	printf("in main..\n");
	block_Kbyte();
	printf("in main 1..\n");
	block_Mbyte();
	printf("in main 2..\n");
}

int block_Byte()
{
	
	printf("Block size 1 Byte \n");

	int i;
	int len;
	double a=5;
	struct timeval start, end;
	struct timezone tzp;

	char mem = 'C';	
	
	char *mem_write=malloc(sizeof(BLOCK_SIZE));
	//mem_write=(char*)
	//len = strlen(mem)+1;
	int no_bytes= sizeof(mem);

	gettimeofday(&start, &tzp);

	for(i=0;i<BLOCK_SIZE;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
		//printf("memory %p",mem_write);
		//printf("%d",i);
	}

	gettimeofday(&end, &tzp);

	double timeMs = (end.tv_usec - start.tv_usec)/(double)1000;

	double throughput = (BLOCK_SIZE/((double)((1024*1024)*(end.tv_usec-start.tv_usec))))*1000000;

	printf("Throughput for 1B block: %f MB/sec\n\n",throughput);

	printf("Latency is: %f milliseconds\n",timeMs);

}

int block_Kbyte()
{

	printf("Block size 1 KByte \n");
		
	int i;
	int len;
	double a=5;
	struct timeval start, end;
	struct timezone tzp;

	char mem = 'C';	
	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_KB));
	//mem_write=(char*)
	//len = strlen(mem)+1;
	int no_bytes= sizeof(mem);

	gettimeofday(&start, &tzp);

	for(i=0;i<BLOCK_SIZE_KB;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
		//printf("memory %p",mem_write);
		//printf("%d",i);
	}

	gettimeofday(&end, &tzp);

	double timeMs = (end.tv_usec - start.tv_usec)/(double)1000;

	double throughput = (BLOCK_SIZE_KB/((double)((1024*1024)*(end.tv_usec-start.tv_usec))))*1000000;

	printf("Throughput for 1KB block: %f MB/sec\n\n",throughput);

	printf("Latency is: %f milliseconds\n",timeMs);
}

int block_Mbyte()
{
	printf("Block size 1 MByte \n");
	int i;
	int len;
	double a=5;
	struct timeval start, end;
	struct timezone tzp;

	char mem = 'C';	
	
	char *mem_write=malloc(sizeof(BLOCK_SIZE_MB));
	//mem_write=(char*)
	//len = strlen(mem)+1;
	int no_bytes= sizeof(mem);

	gettimeofday(&start, &tzp);

	for(i=0;i<BLOCK_SIZE_MB;i++)
	{
		memcpy(mem_write,&mem,BLOCK_SIZE);
		*(mem_write+i);
		//printf("memory %p",mem_write);
		//printf("%d",i);
	}

	gettimeofday(&end, &tzp);

	double timeMs = (end.tv_usec - start.tv_usec)/(double)1000;

	double throughput = (BLOCK_SIZE_MB/((double)((1024*1024)*(end.tv_usec-start.tv_usec))))*1000000;

	printf("Throughput for 1MB block: %f MB/sec\n\n",throughput);

	printf("Latency is: %f milliseconds\n",timeMs);

//free();
}

