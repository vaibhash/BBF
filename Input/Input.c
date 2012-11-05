// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Definitions for ReadNeedleToBloom
//

#include "Input.h"


_uint FindNeedleHayStack(_string fileHayStack, _byte* in_buffer, _int windowSize)
{

	_uint count = 0;
	_long position=1;
	if(!fileHayStack)
	{

		printf("File name is NULL\n");
		return 0;

	}
	_byte *buffer = NULL;
	buffer = (_byte *)malloc(sizeof(_byte)*(windowSize+1));
	
	if(NULL==buffer)
	{
		printf("Error in allocating memory for buffer");
		return -1;
	}
	
   	FILE *file = fopen ( fileHayStack, "r" );
   	if(NULL==file)
   	{
   	      		printf("Failed to open Haystack file\n");
      			return -1;
   	
   	}
   	
   	if(fgets ( buffer, windowSize+1, file ) != NULL)
   	{
         	if(!strcmp(in_buffer,buffer))
         	{
         		//printf(" @POSITION %ld\n",position);
         		count++;
         	}
   		position++;	
   	}

	_byte inChar = 0;
	_byte outChar = 0;
	while ( (inChar = getc (file )) != EOF ) 
  	{
		outChar = buffer[0];
         	//
         	//	bad implementation change it 
         	//
		for(int i = 0; i < windowSize-1; i++)
		{
			buffer[i] = buffer[i+1];
		}
		buffer[windowSize-1] = inChar;
       
        	if(!strcmp(in_buffer,buffer))
        	{
        	//	printf(" @POSITION %ld\n",position);
        		count++;
        	}
         	
       		position++;
	}
	fclose(file);
	return count;
}

_ulong NeedleHaystack(_string needle_file,_string haystack_file,  _int windowSize)
{

	_ulong totalCount = 0;
	_uint count = 0;
	_ulong needle_count = 0;
	
      	printf("\nSTART :: Reading NEEDLE\n");
	if(!needle_file)
	{

		printf("File name is NULL\n");
		return 0;

	}
	_byte *buffer = NULL;
	buffer = (_byte *)malloc(sizeof(_byte)*(windowSize+1));
	
	if(NULL==buffer)
	{
		printf("Error in allocating memory for buffer");
		return -1;
	}

	
   	FILE *file = fopen ( needle_file, "r" );
   	if ( file != NULL )
   	{
      		while ( fgets ( buffer, windowSize+1, file ) != NULL ) 
      		{
			if(strlen(buffer)!=(unsigned)windowSize) continue;
         		count = FindNeedleHayStack(haystack_file,buffer,windowSize);
			needle_count++;
			if(count>0)
			{
				totalCount+=count;
			}
			count=0;

      		}
      		fclose ( file );
   	}
   	else
   	{
      		printf("Failed to open needle file\n");
      		printf("\nEND :: Reading NEEDLE\n");
      		return -1;
   	}

   	printf("\nNumber of Needles of %d size scanned %ld\n",windowSize, needle_count);
   	printf("\nNumber of Needles found in haystack %ld\n",totalCount);
   	    
  	printf("\nEND :: Reading NEEDLE\n");	
   	return 0;
}


