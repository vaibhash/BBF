// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Declarations for INPUT file info grabber
//


#ifndef INPUT_H
#define READ_NEEDLES_TO_BLOOM_H

#include "../Include/Types.h"

//
//	Read needle file and fill the bloated bloom filters
//
		_ulong NeedleHaystack(_string needle_file,_string haystack, _int windowSize);
		
//
//	Read needle and update the bloated bloom filter
//
		_uint FindNeedleHaystack(_string haystack_file, _byte* input_buffer,_int windowSize);
		
		//
		
		
#endif
