// 
//	Author : vaibhavs@flux.utah.edu
//	Description: public interfaces for RollOverHash
//


#ifndef ROLL_OVER_HASH_H
#define ROLL_OVER_HASH_H

//
// 	this prints the  content of transformation tables for two hash functions
//
		_bool printArray();

//
//	initialize function
//
		_bool RollOverHash_Init( _int windowSize);

		
//
//	this function takes a string, reads windowSize bytes from it 
//	and create the hash
//
		_ulong firstHash_initialRound(_string buffer);
		_ulong secondHash_initialRound(_string buffer);
				
//
//	this function takes the new char and old char and upates the hash value with minimal 
//	computation
//
		_ulong firstHash_updateRound(_byte oldChar, _byte newChar);
		_ulong secondHash_updateRound(_byte oldChar, _byte newChar);
		

#endif
