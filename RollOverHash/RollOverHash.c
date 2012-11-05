// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of Roll over hash 
//	class specification
//
#include "../Include/Types.h"
#include "../Include/MersenneTwister.h"
#include "RollOverHash.h"

//
//	BIT-wise operation used 
// 
#define AND( A , B )	((A)&(B))
#define XOR( A , B )	((A)^(B))
#define ROTL( A, B )	((A)<<(B))

//
//	Few constant for the RolloverHash 
//
	const _int 	delta = 1;
	const _int 	sizeTable = 256; 
	const _ulong 	AddressMask = LONG_MAX; 

 
//
//	two table of size "sizeTable" which will almost always be 256 
//	which is ascii char set size
//	One table is for adding the new charaters and other one to remove the 
//	old characters from the table
//	Two seperate tables for first and second hash function
//
	_ulong static First_TransformationT[sizeTable] = {0,};
	_ulong static First_TransformationTPrime[sizeTable]= {0,};
	_ulong static Second_TransformationT[sizeTable]= {0,};
	_ulong static Second_TransformationTPrime[sizeTable]= {0,};
	

//
//	windowSize is the size of the data read 
//	and hashWord is the value of the hash for the last string read
//	two seperate long values to store ouput of two rolloverhash values
//
	_int static windowSize;	
	_ulong static first_hashWord;
	_ulong static second_hashWord;



//
//	these function generates the random number which are filled in the first_TransformationT
//	and Second_TransformationT 
//	
	_bool firstHash_ranGenSet();
	_bool firstHash_setTprime();
	_bool secondHash_ranGenSet();
	_bool secondHash_setTprime();
		

_ulong firstHash_initialRound(_string buffer)
{
	
	first_hashWord = 0;
		
	
	for(_int i = 0 ; i < windowSize ; i++ )
	{
		first_hashWord = ROTL(first_hashWord,delta);
		first_hashWord = XOR(first_hashWord,First_TransformationT[buffer[i] & 0xFF]);
	}
	
	first_hashWord = AND(first_hashWord, AddressMask);
	return first_hashWord;

}

_ulong secondHash_initialRound(_string buffer)
{

	second_hashWord = 0;
	for(_int i = 0 ; i < windowSize ; i++ )
	{
		second_hashWord = ROTL(second_hashWord,delta);
		second_hashWord = XOR(second_hashWord,Second_TransformationT[buffer[i] & 0xFF]);
	}
	
	second_hashWord = AND(second_hashWord, AddressMask);
	return second_hashWord;

}

_bool firstHash_setTprime()
{
	for(_int i = 0 ; i < sizeTable ; i++ )
	{
		First_TransformationTPrime[i] = ROTL(First_TransformationT[i],delta*windowSize);
	}
	return true;

}

_bool secondHash_setTprime()
{
	for(_int i = 0 ; i < sizeTable ; i++ )
	{
		Second_TransformationTPrime[i] = ROTL(Second_TransformationT[i],delta*windowSize);
	}
	return true;

}

_ulong firstHash_updateRound(_byte removeChar, _byte addChar)
{

	if(first_hashWord)
	{

			first_hashWord = ROTL(first_hashWord,delta);
			first_hashWord = XOR(first_hashWord,First_TransformationT[addChar & 0xFF]);
			first_hashWord = XOR(first_hashWord,First_TransformationTPrime[removeChar & 0xFF]);
			first_hashWord = AND(first_hashWord,AddressMask);

	}
	else
	{

		printf("run the firstRound and then updateRound\n");
		return -1;

	}
	return first_hashWord;

}

_ulong secondHash_updateRound(_byte removeChar, _byte addChar)
{

	if(second_hashWord)
	{

			second_hashWord = ROTL(second_hashWord,delta);
			second_hashWord = XOR(second_hashWord,Second_TransformationT[addChar & 0xFF]);
			second_hashWord = XOR(second_hashWord,Second_TransformationTPrime[removeChar & 0xFF]);
			second_hashWord = AND(second_hashWord,AddressMask);

	}
	else
	{

		printf("run the firstRound and then updateRound\n");
		return -1;

	}
	return second_hashWord;

}



_bool firstHash_ranGenSet()
{
	MTRand mtrand;
	for( _int i = 0 ; i < sizeTable ; i++ )
	{
		First_TransformationT[i] = mtrand.randInt();
	}
	return true;
}

_bool secondHash_ranGenSet()
{
	MTRand mtrand;
	for( _int i = 0 ; i < sizeTable ; i++ )
	{
		Second_TransformationT[i] = mtrand.randInt();
	}
	return true;
}


_bool printArray()
{
	printf("\nFirst_Table= { \n");
	for( _int i = 0 ; i < sizeTable / 8 ; i++  )
	{
		for( _int j = 0 ; j < 8 ; j++ )
		{
			printf("0x%-8X, ",(unsigned)First_TransformationT[j*8+i]);
		}
		printf("\n");
	}
	printf("\t}\n");
	printf("\nSecond_Table= { \n");
	for( _int i = 0 ; i < sizeTable / 8 ; i++  )
	{
		for( _int j = 0 ; j < 8 ; j++ )
		{
			printf("0x%-8X, ",(unsigned)Second_TransformationT[j*8+i]);
		}
		printf("\n");
	}
	printf("\t}\n");
	return true;
}


_bool RollOverHash_Init( _int window = 10 )
{
			windowSize = window;
			{	
				firstHash_ranGenSet();
				firstHash_setTprime();
				first_hashWord = 0;
			}
			{
				secondHash_ranGenSet();
				secondHash_setTprime();
				second_hashWord = 0;
			}
			return true;
}

/*
int main( int argc , char *argv[] )
{

	RollOverHash_Init();
	printArray();
	printf("%ld\n",firstHash_initialRound("vaibhavsha"));
	printf("%ld\n",firstHash_updateRound('v','r'));
	printf("%ld\n",firstHash_initialRound("vaibhavsha"));
	printf("%ld\n",firstHash_updateRound('v','r'));
	printf("%ld\n",secondHash_initialRound("vaibhavsharma"));
	printf("%ld\n",second_updateRound('v','r'));
	printf("%ld\n",secondHash_initialRound("vaibhavsharma"));
	printf("%ld\n",second_updateRound('v','r'));

}
*/

