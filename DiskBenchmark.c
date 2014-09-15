#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>

void fileWrite()
{
	FILE *fp;
	char c[]="Program to find Throughput and latency";
	char buffer[30];
	struct timeval start, end;
    	struct timezone tzp;
	
	printf("\n\nFile Write operation:\n..................");
	
	gettimeofday(&start, &tzp);
	//Open file for writing
	fp = fopen("file.txt", "w+");

   	// Write data to the file
   	fwrite(c, strlen(c) + 1, 1, fp);
   	printf("\nSizeof file to be written %lu bytes",sizeof(c));

	/* Seek to the beginning of the file */
   	//fseek(fp, SEEK_SET, 0);
   	
	if(fp == NULL)
    	{
        	printf("\n fopen() Error!!!\n");
    	}
    	
    	gettimeofday(&end, &tzp);
    	
    	//Calculate Latency in milliseconds
    	double latency= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	double througput=(sizeof(c)/((double)(1048576*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	fclose(fp);
}

void fileRead()
{
	FILE *fp;
	char buffer[40];
	struct timeval start, end;
    	struct timezone tzp;
    	
    	printf("\n\nFile Read operation:\n..................");

	gettimeofday(&start, &tzp);
	//Open file for reading
	fp = fopen("file.txt", "r+");
   	
	if(fp == NULL)
    	{
        	printf("\n fopen() Error!!!\n");
    	}
    	   	
    	fread(buffer, sizeof(buffer), 1, fp);
    	gettimeofday(&end, &tzp);
    	printf("\nSizeof file to read %lu bytes",ftell(fp));
 	printf("\nFile contents:%s\n", buffer);

 	//Calculate Latency in milliseconds
    	double latency= (end.tv_usec - start.tv_usec)/(double)1000;
    	printf("\nLatency : %f ms",latency);
    	
    	//Calculate throughput in MB/Sec
    	double througput=(sizeof(buffer)/((double)(1048576*(end.tv_usec - start.tv_usec))))*1000000;
    	printf("\nThroughtput:%f MB/s",througput);
    	
    	fclose(fp);
}

void main()
{	
    	//pthread_t pth1, pth2,pth3,pth4;		
	printf("\nProgram to find Disk Benchmark\n.................\n..................");
	fileWrite();
	fileRead();
	printf("\n");
}
