// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Implementation of Roll over hash 
//	class specification
//

#include "RollOverHash.h"

 
//
//	definitions of the data
//
//
	_ulong First_TransformationT[sizeTable] = {0,};
	_ulong First_TransformationTPrime[sizeTable]= {0,};
	_ulong Second_TransformationT[sizeTable]= {0,};
	_ulong Second_TransformationTPrime[sizeTable]= {0,};
	
	_int windowSize;
	
	_ulong first_hashWord;
	_ulong second_hashWord;


_ulong first_firstRound(_string buffer)
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

_ulong second_firstRound(_string buffer)
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

_bool first_setTprime()
{
	for(_int i = 0 ; i < sizeTable ; i++ )
	{
		First_TransformationTPrime[i] = ROTL(First_TransformationT[i],delta*windowSize);
	}
	return true;

}

_bool second_setTprime()
{
	for(_int i = 0 ; i < sizeTable ; i++ )
	{
		Second_TransformationTPrime[i] = ROTL(Second_TransformationT[i],delta*windowSize);
	}
	return true;

}

_ulong first_updateRound(_byte removeChar, _byte addChar)
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

_ulong second_updateRound(_byte removeChar, _byte addChar)
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



_bool first_ranGenSet()
{
	MTRand mtrand;
	for( _int i = 0 ; i < sizeTable ; i++ )
	{
		First_TransformationT[i] = mtrand.randInt();
	}
	return true;
}

_bool second_ranGenSet()
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
			first_ranGenSet();
			first_setTprime();
			first_hashWord = 0;
			second_ranGenSet();
			second_setTprime();
			second_hashWord = 0;
			return true;
}

/*
int main( int argc , char *argv[] )
{

	RollOverHash_Init();
	printArray();
	printf("%ld\n",first_firstRound("vaibhavsha"));
	printf("%ld\n",first_updateRound('v','r'));
	printf("%ld\n",first_firstRound("vaibhavsha"));
	printf("%ld\n",first_updateRound('v','r'));
	printf("%ld\n",second_firstRound("vaibhavsharma"));
	printf("%ld\n",second_updateRound('v','r'));
	printf("%ld\n",second_firstRound("vaibhavsharma"));
	printf("%ld\n",second_updateRound('v','r'));

}
*/
