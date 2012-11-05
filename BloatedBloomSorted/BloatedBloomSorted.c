// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of BloatedBloomSortedFilter 
//	
//


#include "../Include/Types.h"
#include "BloatedBloomSorted.h"

static _byte *BloatedBloomSorted_Vector = NULL;

static _ulong size_bb = 0;	

static _ulong hashValues[4] = {0,};

_bool BloatedBloomSorted_Init(_ulong vector_size)
{
	BloatedBloomSorted_Vector =  new _byte[vector_size/2+vector_size%2]();
	size_bb = vector_size;
	return true;
}

_bool BloatedBloomSorted_Close()
{
	delete [] BloatedBloomSorted_Vector;
	size_bb = 0;
	return true;
}



void swap_values(_ulong *A, _ulong *B) { _ulong temp = *A; *A = *B; *B = temp; }


//Takes numbers {a,b,c,d}, split into 2 sets {a,b} {c,d}. Order each of those 2 set. That's one comparison per set.
//Now pick lowest from the front (compare a,c). That's now three comparisons. 
//Pick next lowest from either (b, d).That's four. 
//and finallly compare the (b,c)

void sort_four_numbers(_ulong a[])
{
	if(a[0]>a[1]) swap_values(a+0,a+1);
	if(a[2]>a[3]) swap_values(a+2,a+3);
	if(a[0]>a[2]) swap_values(a+0,a+2);
	if(a[1]>a[3]) swap_values(a+1,a+3);
	if(a[1]>a[2]) swap_values(a+1,a+2);
	return;

}


void static setbit(int index)
{
	_byte or_value = 1<<index;


	_ulong nibble_index = hashValues[index]%size_bb;
	if(nibble_index%2)
	{
		BloatedBloomSorted_Vector[nibble_index/2]|=(or_value<<4);
	}
	else
	{
		BloatedBloomSorted_Vector[nibble_index/2 + 1]|=(or_value);
	}

}

_bool static getbit(int index)
{
	_byte or_value = 1<<index;

	_ulong nibble_index = hashValues[index]%size_bb;
	if(nibble_index%2)
	{
		return BloatedBloomSorted_Vector[nibble_index/2]&(or_value<<4);
	}
	else
	{
		return BloatedBloomSorted_Vector[nibble_index/2 + 1]&(or_value);
	}
	return false;

}



void fillHashValuesSorted(_long firstHash, _long secondHash)
{

	hashValues[0] = (_ulong)firstHash;
	hashValues[1] = (_ulong)secondHash;
	hashValues[2] = hashValues[0]+hashValues[1]; 
	hashValues[3] = hashValues[2]+hashValues[1];
	sort_four_numbers(hashValues);
}




_bool BloatedBloomSortedAddToFilter(_long firstHash, _long secondHash)
{
	fillHashValuesSorted(firstHash,secondHash);

	setbit(0);
	setbit(1);
	setbit(2);
	setbit(3);
	return true;

}





_int queryBloatedBloomSortedFilter(_long firstHash, _long secondHash)
{

	fillHashValuesSorted(firstHash,secondHash);


	if(!getbit(0))return false;
	if(!getbit(1))return false;
	if(!getbit(2))return false;
	if(!getbit(3))return false;
	return true;
}
     


void printBloatedSorted()
{
	_ulong j;
	_ulong counter = size_bb/2+size_bb%2;

	printf("Start printing vectors\n");
	for(j=0;j<counter;j++)
	{
		if(BloatedBloomSorted_Vector[j]!=0)
		{
				printf("index %ld value %d\n",j,BloatedBloomSorted_Vector[j]);
		}
	}
	
	printf("End printing vectors\n");
	return;
}


void printBloatedSortedStat()
{
	
	printf("\nBLOATED SORTED MEM INFO\n");
	printf("Total memory used %ld\n",sizeof(_byte)*(size_bb/2+size_bb%2));
	printf("Number of index provided %ld\n\n",size_bb);
	return;
}
	


