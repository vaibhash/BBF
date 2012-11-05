// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of BloatedBloomFilter 
//	
//


#include "../Include/Types.h"
#include "BloatedBloom.h"
typedef struct{
	_ulong min;
	_ulong max;
}minmax;

_byte VectorBloatedBloom[Index_BB/2+Index_BB%2] = {0,};
_ulong hashValues[4] = {0,};
_ulong size_bb = Index_BB;	
node* hash[4] = {NULL,NULL,NULL,NULL};
minmax layer[4] = {{0,0},};    
// function to keep track of collison 
//   from same hash function
//    
    
int AddList(_ulong hashValue, node** headnode)
{
	node * temp;
	node *pointer = *headnode;
	if(*headnode == NULL)
	{
		temp = (node*)malloc(sizeof(node));
		temp->next = NULL;
		temp->count=0;
		temp->hValue = hashValue;
		*headnode = temp;
		return 0;
	}
	while(pointer->next!=NULL)
	{
		if((_ulong)pointer->hValue == hashValue)
		{
			 pointer->count+=1;
			 return -1;
		}
		pointer= pointer->next;
	}
	temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
	temp->count=0;
	temp->hValue = hashValue;
	pointer->next = temp;
	return 0;
	
}


//
// function to free the memory alocated to the linklist
//
//

void DeleteList(node* headnode)
{
	node *pointer = headnode;
	node *next;
	while(pointer)
	{
		next = pointer->next;
		free(pointer);
		pointer = next;
	}
}


//
//   function to print the values
//   which had collison 
//
void PrintList(node* headnode)
{
	_uint count=0;
	if(headnode==NULL)
	{
		printf("Empty list\n");
	}
	while(headnode!=NULL)
	{
		if(headnode->count!=0)
		{
			count+=(headnode->count);	
		}
	    headnode=headnode->next;
    }
    printf("\nNumber of Collisons %d",count);
}






void swapp(_ulong *A, _ulong *B) { _ulong temp = *A; *A = *B; *B = temp; }


//Takes numbers {a,b,c,d}, split into 2 sets {a,b} {c,d}. Order each of those 2 set. That's one comparison per set.

//Now pick lowest from the front (compare a,c). That's now three comparisons. 
//Pick next lowest from either (b, d).That's four. 
//and finallly compare the (b,c)


void sort_four_numbers(_ulong a[])
{
	if(a[0]>a[1]) swapp(a+0,a+1);
	if(a[2]>a[3]) swapp(a+2,a+3);
	if(a[0]>a[2]) swapp(a+0,a+2);
	if(a[1]>a[3]) swapp(a+1,a+3);
	if(a[1]>a[2]) swapp(a+1,a+2);
	return;

}



void fillHashValues(_long firstHash, _long secondHash)
{

	hashValues[0] = (_ulong)firstHash;
	hashValues[1] = (_ulong)secondHash;
	hashValues[2] = hashValues[0]+hashValues[1]; 
	hashValues[3] = hashValues[2]+hashValues[1];
}

void fillHashValues_sorted(_long firstHash, _long secondHash)
{

	hashValues[0] = (_ulong)firstHash;
	hashValues[1] = (_ulong)secondHash;
	hashValues[2] = hashValues[0]+hashValues[1]; 
	hashValues[3] = hashValues[2]+hashValues[1];
	sort_four_numbers(hashValues);
}

void setbit(int index)
{
	_byte or_value = 1<<index;


	_ulong nibble_index = hashValues[index]%size_bb;
	if(layer[index].min==0||layer[index].min>nibble_index)layer[index].min = nibble_index;
	if(layer[index].max<nibble_index)layer[index].max = nibble_index;
	if(nibble_index%2)
	{
		VectorBloatedBloom[nibble_index/2]|=(or_value<<4);
	}
	else
	{
		VectorBloatedBloom[nibble_index/2 + 1]|=(or_value);
	}

	//AddList(hashValues[index],&hash[index]);
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

_bool BloatedBloomAddToFilter_sorted(_long firstHash, _long secondHash)
{
	fillHashValues_sorted(firstHash,secondHash);

	setbit(0);
	setbit(1);
	setbit(2);
	setbit(3);
	return true;

}

_bool getbit(int index)
{
	_byte or_value = 1<<index;

	_ulong nibble_index = hashValues[index]%size_bb;
	if(nibble_index%2)
	{
		return VectorBloatedBloom[nibble_index/2]&(or_value<<4);
	}
	else
	{
		return VectorBloatedBloom[nibble_index/2 + 1]&(or_value);
	}
	return false;

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
     

_int queryBloatedBloomFilter_sorted(_long firstHash, _long secondHash)
{

	fillHashValues_sorted(firstHash,secondHash);
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
		if(VectorBloatedBloom[j]!=0)
		{
				printf("index %ld value %d\n",j,VectorBloatedBloom[j]);
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
	/*
	int i;
	for(i=0;i<4;i++)
	{
		printf("%d : min : %ld , max : %ld\n",(i+1),layer[i].min,layer[i].max);
	}	
	PrintList(hash[0]);
	PrintList(hash[1]);
	PrintList(hash[2]);
	PrintList(hash[3]);
	
	
	DeleteList(hash[0]);
	DeleteList(hash[1]);
	DeleteList(hash[2]);
	DeleteList(hash[3]);
	*/
	
	return;
}
	


