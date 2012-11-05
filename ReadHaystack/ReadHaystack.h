// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Declarations for ReadHaystack
//

#ifndef READ_HAYSTACK_H
#define READ_HAYSTACK_H

#include "../Include/Types.h"

//
//	Read haystack file and check for match in bloom filter
//
		_uint ReadHayStack(_string haystack_file, _int windowSize);
		

//
//	calculate the first hashvalue
//
		_uint ReadHaystackInit(_string query, _int windowSize);
		
//
//	update the hashvalue through update hash functionality 
//
		_uint ReadHaystackUpdate(_byte addChar, _byte removeChar);


//
//	Read haystack file and check for match in bloom filter
//
		_uint ReadHayStackBloom(_string haystack_file, _int windowSize, _int numberHash);
		

//
//	calculate the first hashvalue
//
		_uint ReadHaystackInitBloom(_string query, _int windowSize, _int numberHash);
		
//
//	update the hashvalue through update hash functionality 
//
		_uint ReadHaystackUpdateBloom(_byte addChar, _byte removeChar, _int numberHash);
#endif
