// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Declarations for ReadNeedleToBloom
//


#ifndef READ_NEEDLES_TO_BLOOM_H
#define READ_NEEDLES_TO_BLOOM_H

#include "../Include/Types.h"

//
//	Read needle file and fill the bloated bloom filters
//
		_uint ReadNeedleFileToBloatedBloom(_string needle_file, _int windowSize);
		
//
//	Read needle and update the bloated bloom filter
//
		_bool ReadNeedleToBloatedBloom(_byte *needle, _int windowSize);

//
//	Read needle file and fill the bloated bloom filters
//
		_uint ReadNeedleFileToBloatedBloomSorted(_string needle_file, _int windowSize);
		
//
//	Read needle and update the bloated bloom filter
//
		_bool ReadNeedleToBloatedBloomSorted(_byte *needle, _int windowSize);		
//
//	Read needle file and fill the bloom filters
//
		_uint ReadNeedleFileToBloom(_string needle_file, _int windowSize, _int numberHash);
		
//
//	Read needle and update the bloom filter
//
		_bool ReadNeedleToBloom(_byte *needle, _int windowSize, _int numberHash);
		
		
#endif
