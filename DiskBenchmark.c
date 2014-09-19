#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include<pthread.h>

#define BYTE 1
#define KILOBYTE 1024
#define MEGABYTE 1024*1024

//................................
// 1B block size
//................................
void *fileReadWriteByte()
{
	FILE *fp;
	char c[]="c";
	int i;
	struct timeval start, end;
    	struct timezone tzp;	

	fp = fopen("file.txt", "w+");
	
	//..........................
    	//File  Write operation
    	//..........................
    	printf("\n\nFile Write operation for 1 Byte Block size");
    	char bufferB[BYTE];
	gettimeofday(&start, &tzp);
   	fwrite(c, sizeof(bufferB), 1, fp);
   	printf("\nSizeof file to be written %lu bytes",sizeof(bufferB));
	if(fp == NULL)
    	{
        	printf("\n fopen() Error!!!\n");
    	}
    	gettimeofday(&end, &tzp);
    	//Calculate Latency in milliseconds
    	double latency= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nLatency : %f ms",latency);
    	//Calculate throughput in MB/Sec
    	double througput=(sizeof(bufferB)/((double)((end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	//............................
    	//File Read operation
    	//...........................
    	printf("\n\nFile read operation for 1 Byte Block size");
	gettimeofday(&start, &tzp);
   	fread(bufferB, sizeof(bufferB), 1, fp);
    	gettimeofday(&end, &tzp);
    	printf("\nSizeof file to read %lu bytes",ftell(fp));
 	printf("\nFile contents:%s", bufferB);

    	//Calculate Latency in milliseconds
    	latency= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nLatency : %f ms",latency);
    	//Calculate throughput in MB/Sec
    	througput=(sizeof(bufferB)/((double)((end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	fclose(fp);
}

//................................
// 1KB block size
//................................
void fileReadWriteKiloByte()
{
	FILE *fp;
	char c[]="c";
	int i;
	struct timeval start, end;
    	struct timezone tzp;	

	fp = fopen("file.txt", "w+");
	
	//..........................
    	//File  Write operation
    	//..........................
    	printf("\n\nFile write operation for 1 Kilo Byte Block size");
    	char bufferKb[KILOBYTE];
    	for(i=0;i<KILOBYTE;i++)
    	{
    		fwrite(c, BYTE, 1, fp);
    	}
   	printf("\nSizeof file to be written %lu bytes",sizeof(bufferKb));
    	gettimeofday(&end, &tzp);
    	
    	//Calculate Latency in milliseconds
    	double latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	double througput=(sizeof(bufferKb)/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	
    	//............................
    	//File Read operation
    	//...........................
    	printf("\n\nFile read operation for 1 Kilo Byte Block size");
	gettimeofday(&start, &tzp);
   	fread(bufferKb, sizeof(bufferKb), 1, fp);
    	gettimeofday(&end, &tzp);
    	printf("\nSizeof file to read %lu bytes",ftell(fp));
 	//printf("\nFile contents:%s", bufferKb);

    	//Calculate Latency in milliseconds
    	latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	througput=(sizeof(bufferKb)/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	
    	fclose(fp);
}

//................................
// 1MB block size
//................................
void fileReadWriteMegaByte()
{
	FILE *fp;
	char c[]="c";
	int i;
	struct timeval start, end;
    	struct timezone tzp;	

	fp = fopen("file.txt", "w+");
	
	//..........................
    	//File  Write operation
    	//..........................
    	printf("\n\nFile write operation for 1 Mega Byte Block size");
    	char bufferMb[MEGABYTE];
    	for(i=0;i<MEGABYTE;i++)
    	{
    		fwrite(c, BYTE, 1, fp);
    	}
   	printf("\nSizeof file to be written %lu bytes",sizeof(bufferMb));
    	gettimeofday(&end, &tzp);
    	
    	//Calculate Latency in milliseconds
    	double latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	double througput=(sizeof(bufferMb)/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	
    	//............................
    	//File Read operation
    	//...........................
    	printf("\n\nFile read operation for 1 Mega Byte Block size");
	gettimeofday(&start, &tzp);
   	fread(bufferMb, sizeof(bufferMb), 1, fp);
    	gettimeofday(&end, &tzp);
    	//printf("\nSizeof file to read %lu bytes",ftell(fp));
 	//printf("\nFile contents:%s", bufferMb);

    	//Calculate Latency in milliseconds
    	latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	througput=(sizeof(bufferMb)/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	
    	fclose(fp);
}


void main()
{	
    	//pthread_t pth1, pth2,pth3,pth4;		
	printf("\nProgram to find Disk Benchmark\n.................\n..................");
	pthread_t th[10];// array of threads
	int i;
	
    	for(i=0;i<2;i++)
	{
		pthread_create(&th[i],NULL,fileReadWriteByte,NULL);
		pthread_join(th[i], NULL);
	}
    	
	fileReadWriteByte();
	//fileReadWriteKiloByte();
	//fileReadWriteMegaByte();
	
	printf("\n");
}
