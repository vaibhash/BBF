// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Declarations for RolloverHash
//


#ifndef ROLL_OVER_HASH_H
#define ROLL_OVER_HASH_H

#include "../Include/Types.h"
#include "../Include/MersenneTwister.h"





//
//	BIT-wise operation used 
// 
#define AND( A , B )	((A)&(B))
#define XOR( A , B )	((A)^(B))
#define ROTL( A, B )	((A)<<(B))

//
//	Few constant for the RolloverHash 
//	todo: enable functionality to modify these at runtime or to atleast compile time
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
		extern _ulong First_TransformationT[sizeTable];
		extern _ulong First_TransformationTPrime[sizeTable];
		extern _ulong Second_TransformationT[sizeTable];
		extern _ulong Second_TransformationTPrime[sizeTable];

//
//	windowSize is the size of the data read 
//	and hashWord is the value of the hash for the last string read
//	two seperate long values to store ouput of two rolloverhash values
//
		extern _int windowSize;
		extern _ulong first_hashWord;
		extern _ulong second_hashWord;
		
		
		extern node* Fhash;
        extern node* Shash;

//
//	this function generates the random number which are filled in the first_TransformationT
//	and Second_TransformationT 
//	
		_bool first_ranGenSet();
		_bool first_setTprime();
		_bool second_ranGenSet();
		_bool second_setTprime();
		
//
// 	this prints the  content of transformation tables for two hash functions
//
		_bool printArray();

//
//	Intialize function
//
		_bool RollOverHash_Init( _int windowSize);


		
//
//	this function takes a string, reads windowSize bytes from it 
//	and create the hash
//
		_ulong first_firstRound(_string buffer);
		_ulong second_firstRound(_string buffer);
		


		
//
//	this function takes the new char and old char and upates the hash value with minimal 
//	computation
//
		_ulong first_updateRound(_byte oldChar, _byte newChar);
		_ulong second_updateRound(_byte oldChar, _byte newChar);
		

#endif
