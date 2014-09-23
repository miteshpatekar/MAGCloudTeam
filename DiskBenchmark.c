#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include<pthread.h>

#define BYTE 1
#define KILOBYTE 1024
#define MEGABYTE 1024*1024

#define BITERATIONS 10000000
#define KBITERATIONS 1000
#define MBITERATIONS 10

//................................
// 1B block size
//................................
void *fileWriteByteSequential()
{
	FILE *fp;
	char c='c';
	int i;	
	fp = fopen("file.txt", "w+");	
	for(i=0;i<BITERATIONS;i++)
	{
   		fputc(c,fp);
   	}
    	fclose(fp);
}

void *fileWriteByteRandom()
{	
	FILE *fp;
	char c='c';
	int i;	
	fp = fopen("file.txt", "w+");	
	//char bufferB[BYTE];
	for(i=0;i<BITERATIONS;i++)
	{
		fputc(c,fp);
   	}
    	fclose(fp);	
}

void *fileReadByteSequential()
{
	FILE *fp;
	int i;
	char bufferB[BYTE];	
	fp = fopen("file.txt", "r+");
	for(i=0;i<BITERATIONS;i++)
	{
		fread(bufferB, 1, BYTE, fp);
	}
    	fclose(fp);
}

void *fileReadByteRandom()
{
	FILE *fp;
	char c[]="c";
	int i;
	char bufferB[BYTE];	
	fp = fopen("file.txt", "r+");
	for(i=0;i<BITERATIONS;i++)
	{
		fread(bufferB, 1, BYTE, fp);
	}
    	fclose(fp);
}


//................................
// 1KB block size
//................................
void *fileWriteKiloByteSequential()
{
	FILE *fp;
	int i,j;
	char c[KILOBYTE];
	for(j=0;j<KILOBYTE;j++)
	{
		c[j]='m';	
	}
	
	fp = fopen("file.txt", "w+");
	//char bufferKb[KILOBYTE];
    	for(i=0;i<KBITERATIONS;i++)
    	{
    		fwrite(c, 1, KILOBYTE, fp);
    	}
    	
    	fclose(fp);
}

void *fileWriteKiloByteRandom()
{
	FILE *fp;
	int i,j;
	char c[KILOBYTE];
	for(j=0;j<KILOBYTE;j++)
	{
		c[j]='m';	
	}
	fp = fopen("file.txt", "w+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KBITERATIONS;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fwrite(c, 1, KILOBYTE, fp);
    	}
    	
    	fclose(fp);
}

void *fileReadKiloByteSequential()
{
	FILE *fp;
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KBITERATIONS;i++)
    	{
    		fread(bufferKb, KILOBYTE, 1, fp);
    	}
    	fclose(fp);
}

void *fileReadKiloByteRandom()
{
	FILE *fp;
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[KILOBYTE];
    	for(i=0;i<KBITERATIONS;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fread(bufferKb, KILOBYTE, 1, fp);
    	}
    	fclose(fp);
}



//................................
// 1MB block size
//................................
void *fileWriteMegaByteSequential()
{
	FILE *fp;
	int i,j;
	char c[MEGABYTE];
	for(j=0;j<MEGABYTE;j++)
	{
		c[j]='m';	
	}
	fp = fopen("file.txt", "w+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MBITERATIONS;i++)
    	{
    		fwrite(c, 1, MEGABYTE, fp);
    	}
    	fclose(fp);
}

void *fileWriteMegaByteRandom()
{
	FILE *fp;
	int i,j;
	char c[MEGABYTE];
	for(j=0;j<MEGABYTE;j++)
	{
		c[j]='m';	
	}
	fp = fopen("file.txt", "w+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MBITERATIONS;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fwrite(c, 1, MEGABYTE, fp);
    	}
  
    	fclose(fp);
}

void *fileReadMegaByteSequential()
{
	FILE *fp;
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MBITERATIONS;i++)
    	{
    		fread(bufferKb, MEGABYTE, 1, fp);
    	}
    	fclose(fp);
}

void *fileReadMegaByteRandom()
{
	FILE *fp;
	int i;
	fp = fopen("file.txt", "r+");
	char bufferKb[MEGABYTE];
    	for(i=0;i<MBITERATIONS;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(fp,r,SEEK_SET); 
    		fread(bufferKb, MEGABYTE, 1, fp);
    	}
    	fclose(fp);
}


void main()
{	
	struct timeval start, end;
    	struct timezone tzp;
    	clock_t startTime, endTime;
    	double timeDiff,latency,throughput;
    			
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
			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BITERATIONS/(double)(latency*MEGABYTE));
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			//Random Write
			printf("\n\nRANDOM Write");
			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BITERATIONS/(double)(latency*MEGABYTE));
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			
    			//Sequential Read
			printf("\n\nSEQUENTIAL Read");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=(BITERATIONS/(double)(latency*MEGABYTE));
    			printf("\nThroughtput:%f MB/s",throughput);
    			
    			//Random Read
			printf("\n\nRANDOM Read");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=((BITERATIONS)/(double)(latency*MEGABYTE));
    			printf("\nThroughtput:%f MB/s",throughput);
    			
			break;
		case 2: //Sequential Write KiloByte
			printf("\n\nSEQUENTIAL Write KiloByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteKiloByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
			printf("\nLatency : %f ms",latency);
			throughput=(KBITERATIONS*1000)/(double)(latency*KILOBYTE);
    			printf("\nThroughtput:%f MB/s",throughput);
			
			//Random Write KiloByte
			printf("\n\nRANDOM Write KiloByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteKiloByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
			printf("\nLatency : %f ms",latency);
			throughput=(KBITERATIONS*1000)/(double)(latency*KILOBYTE);
    			printf("\nThroughtput:%f MB/s",throughput);
			
			//Sequential Read KiloByte
			printf("\n\nSEQUENTIAL Read KiloByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadKiloByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
			printf("\nLatency : %f ms",latency);
			throughput=(KBITERATIONS*1000)/(double)(latency*KILOBYTE);
    			printf("\nThroughtput:%f MB/s",throughput);
			
    			//Random Read KiloByte
			printf("\n\nRandom Read KiloByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadKiloByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
			printf("\nLatency : %f ms",latency);
			throughput=(KBITERATIONS*1000)/(double)(latency*KILOBYTE);
    			printf("\nThroughtput:%f MB/s",throughput);
			break;
		case 3: //Sequential Write MegaByte
			printf("\n\nSEQUENTIAL Write MegaByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteMegaByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=((MBITERATIONS*1000)/((double)(latency)));
    			printf("\nThroughtput:%f MB/s",throughput);		
    			
    			//Random Write MegaByte
			printf("\n\nRANDOM Write MegaByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileWriteMegaByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=((MBITERATIONS*1000)/((double)(latency)));
    			printf("\nThroughtput:%f MB/s",throughput);		
    			
			//Sequential Read MegaByte
			printf("\n\nSequential Read MegaByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadMegaByteSequential,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=((MBITERATIONS*1000)/((double)(latency)));
    			printf("\nThroughtput:%f MB/s",throughput);		
    			
    			//Random Read MegaByte
			printf("\n\nRandom Read MegaByte");
    			startTime=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,fileReadMegaByteRandom,NULL);
				pthread_join(th[i], NULL);
			}
			endTime = clock();
			timeDiff = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    			latency= (timeDiff*1000)/(double)(nthread);
    			printf("\nLatency : %f ms",latency);
    			throughput=((MBITERATIONS*1000)/((double)(latency)));
    			printf("\nThroughtput:%f MB/s",throughput);				
    				
			break;
		case 4: exit(0);
			break;
		default:printf("/nOOPSS...Please enter valid input");			
	}
	};	
    	
}
