// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of BloatedBloomFilter 
//	
//


#include "../Include/Types.h"
#include "BloatedBloom.h"

static _byte *BloatedBloom_Vector = NULL;

static _ulong size_bb = 0;	

static _ulong hashValues[4] = {0,};

_bool BloatedBloom_Init(_ulong vector_size)
{
	BloatedBloom_Vector =  new _byte[vector_size/2+vector_size%2]();
	size_bb = vector_size;
	return true;
}

_bool BloatedBloom_Close()
{
	delete [] BloatedBloom_Vector;
	size_bb = 0;
	return true;
}

void fillHashValues(_long firstHash, _long secondHash)
{

	hashValues[0] = (_ulong)firstHash;
	hashValues[1] = (_ulong)secondHash;
	hashValues[2] = hashValues[0]+hashValues[1]; 
	hashValues[3] = hashValues[2]+hashValues[1];
}


void  static setbit(int index)
{
	_byte or_value = 1<<index;


	_ulong nibble_index = hashValues[index]%size_bb;
	if(nibble_index%2)
	{
		BloatedBloom_Vector[nibble_index/2]|=(or_value<<4);
	}
	else
	{
		BloatedBloom_Vector[nibble_index/2 + 1]|=(or_value);
	}
}


_bool static getbit(int index)
{
	_byte or_value = 1<<index;

	_ulong nibble_index = hashValues[index]%size_bb;
	if(nibble_index%2)
	{
		return BloatedBloom_Vector[nibble_index/2]&(or_value<<4);
	}
	else
	{
		return BloatedBloom_Vector[nibble_index/2 + 1]&(or_value);
	}
	return false;

}


_bool BloatedBloomAddToFilter(_long firstHash, _long secondHash)
{
	fillHashValues(firstHash,secondHash);

	setbit(0);
	setbit(1);
	setbit(2);
	setbit(3);
	return true;

}





_int queryBloatedBloomFilter(_long firstHash, _long secondHash)
{

	fillHashValues(firstHash,secondHash);


	if(!getbit(0))return false;
	if(!getbit(1))return false;
	if(!getbit(2))return false;
	if(!getbit(3))return false;
	return true;
}
     

void printBloated()
{
	_ulong j;
	_ulong counter = size_bb/2+size_bb%2;

	printf("Start printing vectors\n");
	for(j=0;j<counter;j++)
	{
		if(BloatedBloom_Vector[j]!=0)
		{
				printf("index %ld value %d\n",j,BloatedBloom_Vector[j]);
		}
	}
	
	printf("End printing vectors\n");
	return;
}


void printBloatedStat()
{
	
	printf("\nBLOATED MEM INFO\n");
	printf("Total memory used %ld\n",sizeof(_byte)*(size_bb/2+size_bb%2));
	printf("Number of index provided %ld\n\n",size_bb);
	return;
}
	


