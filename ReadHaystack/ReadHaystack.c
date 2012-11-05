// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Definitions for ReadHaystack
//

#include "../Include/Types.h"
#include "../RollOverHash/RollOverHash.h"
#include "../BloatedBloom/BloatedBloom.h"
#include "../BloatedBloomSorted/BloatedBloomSorted.h"
#include "../Bloom/Bloom.h"
#include "ReadHaystack.h"


//
//    Functions for the reading haystack through standard bloated bloom
//
//


_uint ReadHaystackInit(_string buffer, _int windowSize)
{
	_int result = 0;
	_long firstHashValue = 0, secondHashValue = 0;
	
	if(strlen(buffer)==(unsigned)windowSize)
	{
		firstHashValue = firstHash_initialRound(buffer);
		secondHashValue = secondHash_initialRound(buffer);
		result = queryBloatedBloomFilter(firstHashValue, secondHashValue);		
		return result;
		
	}
	else
	{
		printf("buffer size mismatch\n");
	}
	return -1;
   	
}
   	
   	
   	
   	
_uint ReadHaystackUpdate(_byte inChar, _byte outChar)
{
	_int result = 0;
    	_long firstHashValue = 0, secondHashValue = 0;
    
    	firstHashValue = firstHash_updateRound((_byte)outChar , (_byte)inChar);
    	secondHashValue = secondHash_updateRound((_byte)outChar , (_byte)inChar);
   	result = queryBloatedBloomFilter(firstHashValue, secondHashValue);
   	
	return result;
	
       		
}


_uint ReadHayStack(_string fileHayStack, _int windowSize)
{

	_uint count = 0;
	_long position=1;
	printf("\nSTART :: Reading Haystack : BLOATED BLOOM\n");
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
      			printf("\nEND :: Reading HAYSTACK and CHECK BLOATED BLOOM\n");
      			return -1;
   	
   	}
   	
   	if(fgets ( buffer, windowSize+1, file ) != NULL)
   	{
         	if(ReadHaystackInit(buffer,windowSize))
         	{
         		//printf(" @POSITION %ld\n",position);
         		count++;
         	}
   		position++;	
   	}
   	
	_byte inChar = 0;
	_byte outChar = 0;
	
   	 while ( (inChar = getc (file ) )!= EOF ) 
    	{
       		outChar = buffer[0];
       		//
       		//	bad implementation change it 
       		//
       		for(int i = 0; i < windowSize - 1; i++)
       		{
       			buffer[i] = buffer[i+1];
       		}
       		buffer[windowSize-1] = (_byte)inChar;	
		
       		if(ReadHaystackUpdate(inChar, outChar))
       		{
       			count++;
       		}
         	
         	
    		position++;

         	
    	}
      	
    	fclose ( file );
	BloatedBloom_Close();

   	printf("\nNumber of Needles found in haystack %d\n", count);
   	printf("\nTotal strings matched %ld\n",position);
  	printf("\nEND :: Reading HAYSTACK :: BLOATED BLOOM\n");	
   	return 0;
}




//
//    Functions for the reading haystack through sorted bloated bloom
//
//



_uint ReadHaystackInitSorted(_string buffer, _int windowSize)
{
	_int result = 0;
	_long firstHashValue = 0, secondHashValue = 0;
	
	if(strlen(buffer)==(unsigned)windowSize)
	{
		firstHashValue = firstHash_initialRound(buffer);
		secondHashValue = secondHash_initialRound(buffer);
		result = queryBloatedBloomSortedFilter(firstHashValue, secondHashValue);
	
		return result;
		
	}
	else
	{
		printf("buffer size mismatch\n");
	}
	return -1;
   	
}
   	
   	
   	
   	
_uint ReadHaystackUpdateSorted(_byte inChar, _byte outChar)
{
	_int result = 0;
    	_long firstHashValue = 0, secondHashValue = 0;
    
    	firstHashValue = firstHash_updateRound((_byte)outChar , (_byte)inChar);
    	secondHashValue = secondHash_updateRound((_byte)outChar , (_byte)inChar);
   	
   	result = queryBloatedBloomSortedFilter(firstHashValue, secondHashValue);
	return result;
	
       		
}

_uint ReadHayStackSorted(_string fileHayStack, _int windowSize)
{

	_uint count = 0;
	_long position=1;
	printf("\nSTART :: Reading Haystack : BLOATED BLOOM SORTED\n");
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
      			printf("\nEND :: Reading HAYSTACK : BLOATED BLOOM SORTED\n");
      			return -1;
   	
   	}
   	
   	if(fgets ( buffer, windowSize+1, file ) != NULL)
   	{
         	if(ReadHaystackInitSorted(buffer,windowSize))
         	{
         		count++;
         	}
   		position++;	
   	}
   	
	_byte inChar = 0;
	_byte outChar = 0;
	
   	 while ( (inChar = getc (file ) )!= EOF ) 
    	{
       		outChar = buffer[0];
       		//
       		//	bad implementation change it 
       		//
       		for(int i = 0; i < windowSize - 1; i++)
       		{
       			buffer[i] = buffer[i+1];
       		}
       		buffer[windowSize-1] = (_byte)inChar;	
		
       		if(ReadHaystackUpdateSorted(inChar, outChar))
       		{
       			count++;
       		}
         	
         	
    		position++;

         	
    	}
      	
    	fclose ( file );
	BloatedBloomSorted_Close();

   	printf("\nNumber of Needles found in haystack %d\n", count);
   	printf("\nTotal strings matched %ld\n",position);
  	printf("\nEND :: Reading HAYSTACK :: BLOATED BLOOM SORTED\n");	
   	return 0;
}




//
//    Functions for the reading haystack through standard bloom filters
//
//



_uint ReadHaystackInitBloom(_string buffer, _int windowSize, _int numberHash)
{
	_int result = 0;
	_ulong firstHashValue = 0, secondHashValue = 0;
	
   	if(strlen(buffer)==(unsigned)windowSize)
	{
		firstHashValue = firstHash_initialRound(buffer);
		secondHashValue = secondHash_initialRound(buffer);
		result = queryBloomFilter((_ulong)firstHashValue,(_ulong) secondHashValue,numberHash);
		return result;
	}
	else
	{
		printf("buffer size mismatch\n");
	}
	return -1;
   	
}
   	
   	
   	
   	
_uint ReadHaystackUpdateBloom(_byte inChar, _byte outChar,_int numberHash)
{
	_int result = 0;
    	_ulong firstHashValue = 0, secondHashValue = 0;
    
    	firstHashValue = firstHash_updateRound((_byte)outChar,(_byte)inChar);
   	secondHashValue = secondHash_updateRound( (_byte)outChar ,(_byte)inChar);
   		
   	result = queryBloomFilter((_ulong)firstHashValue, (_ulong)secondHashValue,numberHash);
   	
	return result;
	
       		
}

_uint ReadHayStackBloom(_string fileHayStack, _int windowSize, _int numberHash)
{

	_uint count = 0;
	_long position=1;
	printf("\nSTART :: Reading Haystack: BLOOM\n");
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
      			printf("\nEND :: Reading HAYSTACK and CHECK BLOOM\n");
      			return -1;
   	
   	}
   	
   	if(fgets ( buffer, windowSize+1, file ) != NULL)
   	{
         	if(ReadHaystackInitBloom(buffer,windowSize,numberHash))
         	{

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
	
        if(ReadHaystackUpdateBloom(inChar, outChar,numberHash))
        {
        	count++;
        }
         	
       	position++;
         	
    }
      	
  	fclose ( file );
	Bloom_Close();

   	printf("\nNumber of Needles found in haystack %d\n", count);
   	printf("\nTotal strings matched %ld\n",position);
  	printf("\nEND :: Reading HAYSTACK :: BLOOM\n");	
   	return 0;
}



