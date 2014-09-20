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
void *fileWriteByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;	
	fp = fopen("file.txt", "w+");	
	char bufferB[BYTE];
   	fwrite(c, sizeof(bufferB), 1, fp);
    	fclose(fp);
}

void *fileWriteByteRandom()
{	
	FILE *fp;
	char c[]="c";
	int i;	
	fp = fopen("file.txt", "w+");	
	char bufferB[BYTE];
	fseek(fp,1,SEEK_SET);
   	fwrite(c, sizeof(bufferB), 1, fp);
    	fclose(fp);	
}

void *fileReadByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;
	char bufferB[BYTE];	
	fp = fopen("file.txt", "r+");
	fread(bufferB, sizeof(bufferB), 1, fp);
    	fclose(fp);
}

void *fileReadByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	char bufferB[BYTE];	
	fp = fopen("file.txt", "r+");
	fseek(fp,1,SEEK_SET);
	fread(bufferB, sizeof(bufferB), 1, fp);
    	fclose(fp);
}


//................................
// 1KB block size
//................................
void *fileWriteKiloByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "w+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KILOBYTE;i++)
    	{
    		fwrite(c, BYTE, 1, fp);
    	}
    	
    	fclose(fp);
}

void *fileWriteKiloByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "w+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KILOBYTE;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fwrite(c, BYTE, 1, fp);
    	}
    	
    	fclose(fp);
}

void *fileReadKiloByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KILOBYTE;i++)
    	{
    		fread(bufferKb, sizeof(bufferKb), 1, fp);
    	}
    	fclose(fp);
}

void *fileReadKiloByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KILOBYTE;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fread(bufferKb, sizeof(bufferKb), 1, fp);
    	}
    	fclose(fp);
}



//................................
// 1MB block size
//................................
void *fileWriteMegaByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "w+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MEGABYTE;i++)
    	{
    		fwrite(c, BYTE, 1, fp);
    	}
    	
    	fclose(fp);
}

void *fileWriteMegaByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "w+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MEGABYTE;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fwrite(c, BYTE, 1, fp);
    	}
    	
    	fclose(fp);
}

void *fileReadMegaByteSequential()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MEGABYTE;i++)
    	{
    		fread(bufferKb, sizeof(bufferKb), 1, fp);
    	}
    	fclose(fp);
}

void *fileReadMegaByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MEGABYTE;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fread(bufferKb, sizeof(bufferKb), 1, fp);
    	}
    	fclose(fp);
}


void main()
{	
	struct timeval start, end;
    	struct timezone tzp;
    	double latency,throughput;
    			
	printf("\nProgram to find Disk Benchmark\n.................\n..................");
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
	printf("\n\nEnter the number of threads(1/2/4) :\n");
	scanf("%d",&nthread);
	
	switch (ch)
	{
		case 1: //Sequential Write
			printf("\nBYTE read for thread %d",nthread);
			printf("\n\nSEQUENTIAL Write");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BYTE/(double)((latency)*1000));
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			//Random Write
			printf("\n\nRANDOM Write");
			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=BYTE/(double)(latency*1000);
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			
    			//Sequential Read
			printf("\n\nSEQUENTIAL Read");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=BYTE/(double)(latency*1000);
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			//Random Read
			printf("\n\nRANDOM Read");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(nthread*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=BYTE/(double)(latency*1000);
    			printf("\nThroughtput:%f MB/s",throughput);
    			
			break;
		case 2: //Sequential Write KiloByte
			printf("\n\nSEQUENTIAL Write KiloByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteKiloByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KILOBYTE/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);
			
			//Random Write KiloByte
			printf("\n\nRANDOM Write KiloByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteKiloByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KILOBYTE/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);
			
			//Sequential Read KiloByte
			printf("\n\nSEQUENTIAL Write KiloByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadKiloByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
 			latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KILOBYTE/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			//Random Read KiloByte
			printf("\n\nRandom Read KiloByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadKiloByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
 			latency= (end.tv_usec - start.tv_usec)/(double)(KILOBYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(KILOBYTE/((double)(1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);
			break;
		case 3: //Sequential Write MegaByte
			printf("\n\nSEQUENTIAL Write MegaByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteMegaByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MEGABYTE/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);		
    			
    			//Random Write MegaByte
			printf("\n\nRANDOM Write MegaByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteMegaByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MEGABYTE/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);		
			
			//Sequential Read MegaByte
			printf("\n\nSequential Read MegaByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadMegaByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MEGABYTE/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);	
    			
    			//Random Read MegaByte
			printf("\n\nRandom Read MegaByte");
    			gettimeofday(&start, &tzp);
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadMegaByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			gettimeofday(&end, &tzp);
    			latency= (end.tv_usec - start.tv_usec)/(double)(MEGABYTE*1000);
    			printf("\nLatency : %f ms",latency);
    			throughput=(MEGABYTE/((double)(1024*1024*(end.tv_usec - start.tv_usec))))*1000000;
    			printf("\nThroughtput:%f MB/s",throughput);		
    				
			break;
		case 4: exit(0);
			break;
		default:printf("/nOOPSS...Please enter valid input");			
	}
	};	
    	
}
