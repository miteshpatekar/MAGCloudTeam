#include<stdio.h>
#include<sys/time.h>
#include<string.h>

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
	printf("no of bytes=%d",no_bytes);

	gettimeofday(&start, &tzp);

	memcpy(mem_write,mem,len);

	gettimeofday(&end, &tzp);

	double timeMs= (end.tv_usec - start.tv_usec)/(double)1000;
//	printf("\nTime: %f ms\n",timeMs);
	double throughput = (timeMs*1000)/no_bytes;
	printf("Throughput = %f MB/sec \n", throughput);

//	double throughput = timeMs/20;
//	printf("Throughput in bytes/ms = %f\n",throughput);

}
