// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Definitions for ReadNeedleToBloom
//

#include "ReadNeedleToBloom.h"
#include "../RollOverHash/RollOverHash.h"
#include "../BloatedBloom/BloatedBloom.h"
#include "../Bloom/Bloom.h"


_uint count;

_uint ReadNeedleFileToBloatedBloom(_string needle_file, _int windowSize)
{

	count = 0;
	
      	printf("\nSTART :: Reading NEEDLE TO BLOATED\n");
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
	
	RollOverHash_Init(windowSize);
   	FILE *file = fopen ( needle_file, "r" );
   	if ( file != NULL )
   	{
      		while ( fgets ( buffer, windowSize+1, file ) != NULL ) 
      		{
         		ReadNeedleToBloatedBloom(buffer,windowSize);
      		}
      		fclose ( file );
   	}
   	else
   	{
      		printf("Failed to open needle file\n");
      		printf("\nEND :: Reading NEEDLE TO BLOOM\n");
      		return -1;
   	}
   	printf("\nNumber of Needles added to bloom filter %d\n", count);
   	
    
  	printf("\nEND :: Reading NEEDLE TO BLOATED\n");	
   	return 0;
}


_bool ReadNeedleToBloatedBloom(_byte *needle, _int windowSize)
{
	if(strlen(needle)==(unsigned)windowSize)
	{
	   BloatedBloomAddToFilter((_ulong)first_firstRound(needle), (_ulong)second_firstRound(needle));
	   count++;
    	}
    return true;
	
}


_uint ReadNeedleFileToBloom(_string needle_file, _int windowSize, _int numberHash)
{

	count = 0;
	
      	printf("\nSTART :: Reading NEEDLE TO BLOOM\n");
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
	RollOverHash_Init(windowSize);
   	FILE *file = fopen ( needle_file, "r" );
   	if ( file != NULL )
   	{
      		while ( fgets ( buffer, windowSize+1, file ) != NULL ) 
      		{
         		ReadNeedleToBloom(buffer,windowSize,numberHash);
      		}
      		fclose ( file );
   	}
   	else
   	{
      		printf("Failed to open needle file\n");
      		printf("\nEND :: Reading NEEDLE TO BLOOM\n");
      		return -1;
   	}
   	printf("\nNumber of Needles added to bloom filter %d\n", count);
   	
    
  	printf("\nEND :: Reading NEEDLE TO BLOOM\n");	
   	return 0;
}


_bool ReadNeedleToBloom(_byte *needle, _int windowSize, _int numberHash)
{
	if(strlen(needle)==(unsigned)windowSize)
	{
	   BloomAddToFilter(first_firstRound(needle), second_firstRound(needle), numberHash);
	   count++;
	}
    return true;
	
}



