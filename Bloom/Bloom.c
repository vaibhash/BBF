// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of BloomFilter 
//	
//

#include "../Include/Types.h"
#include "Bloom.h"

_bool VectorBloom[Index_B] = {0,};
 
_ulong size_b =  Index_B;

_bool BloomAddToFilter(_ulong firstHash, _ulong secondHash, _int numberHash)
{
	_int i;
	VectorBloom[firstHash%size_b] = 1 ;
	VectorBloom[secondHash%size_b] = 1 ;
	for(i=1;i<numberHash-1;i++)
	{
		VectorBloom[(firstHash+i*secondHash)%size_b] = 1 ;

	}

	return true;
}

_bool printBloom()
{
	_ulong i;
	printf("start of vector\n{\t");
	for(i=0;i<size_b;i++)
	{
		printf("Array[%ld] :: 0x%x,\n",i,VectorBloom[i]);
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
	if( (VectorBloom[firstHash%size_b] == 1) && ( VectorBloom[secondHash%size_b] == 1  )) 
	{
		for(i=1;i<numberHash-1;i++)
		{
			if(VectorBloom[(firstHash+i*secondHash)%size_b] != 1)
			       return 0	;

		}
		return 1;
	}
	else
	{
		return 0;
	}
}



