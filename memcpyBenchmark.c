#include<stdio.h>
#include<sys/time.h>
#include<string.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024

int main(int argc, char *argv[])
{
	
	int i;
	int len;
	double a=5;
	struct timeval start, end;
	struct timezone tzp;

	char mem[] = "Memory Benchmarking using C";	

	char mem_write[100]; 
	len = strlen(mem)+1;
	int no_bytes= sizeof(mem);

	gettimeofday(&start, &tzp);

	memcpy(mem_write,mem,len);

	gettimeofday(&end, &tzp);

	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;

// Throughput for block size = 1B 

	double throughput = (BLOCK_SIZE/((double)(1048576*(end.tv_usec-start.tv_usec))))*1000000;

// Throughput for block size = 1KB 

	double throughput1 = (BLOCK_SIZE_KB/((double)(1048576*(end.tv_usec-start.tv_usec))))*1000000;

// Throughput for block size = 1MB 

	double throughput2 = (BLOCK_SIZE_MB/((double)(1048576*(end.tv_usec-start.tv_usec))))*1000000;

	printf("Throughput for 1KB block: %f MB/sec\n\n",throughput);

	printf("Throughput for 1KB block: %f MB/sec\n\n",throughput1);

	printf("Throughput for 1MB block: %f MB/sec\n\n",throughput2);

	printf("Latency is: %f milliseconds\n",timeMs);

}
