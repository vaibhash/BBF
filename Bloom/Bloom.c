// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of BloomFilter 
//	
//

#include "../Include/Types.h"
#include "Bloom.h"

 static _bool *Bloom_Vector = NULL;
 static _ulong size_b = 0;




_bool Bloom_Init(_ulong vector_size)
{
	Bloom_Vector = new _bool[vector_size]();
	size_b = vector_size;
	return true;	
	
}

_bool  Bloom_Close(void)
{
	delete [] Bloom_Vector;
	size_b = 0;
	return true;
}

_bool BloomAddToFilter(_ulong firstHash, _ulong secondHash, _int numberHash)
{
	_int i;
	Bloom_Vector[firstHash%size_b] = 1 ;
	Bloom_Vector[secondHash%size_b] = 1 ;
	for(i=1;i<numberHash-1;i++)
	{
		Bloom_Vector[(firstHash+i*secondHash)%size_b] = 1 ;

	}

	return true;
}

_bool printBloom()
{
	_ulong i;
	printf("start of vector\n{\t");
	for(i=0;i<size_b;i++)
	{
		printf("Array[%ld] :: 0x%x,\n",i,Bloom_Vector[i]);
	}
	printf("\n}\n");
	return true;
}

_bool printBloomInfo()
{
	printf("\nBLOOM MEM INFO\n");
	printf("Total memory used %ld\n",size_b/8);
	printf("Number of index provided %ld\n\n",size_b);
	return true;
}

_int queryBloomFilter(_ulong firstHash, _ulong secondHash, _int numberHash)
{

	_int i;
	if( (Bloom_Vector[firstHash%size_b] == 1) && ( Bloom_Vector[secondHash%size_b] == 1  )) 
	{
		for(i=1;i<numberHash-1;i++)
		{
			if(Bloom_Vector[(firstHash+i*secondHash)%size_b] != 1)
			       return 0	;

		}
		return 1;
	}
	else
	{
		return 0;
	}
}



