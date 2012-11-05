// 
//	Author : vaibhavs@flux.utah.edu
//	Description: header file of Bloated Bloom
//
#ifndef BLOATED_BLOOM_H
#define BLOATED_BLOOM_H

	_int queryBloatedBloomFilter_sorted(_long firstHash, _long secondHash);

	_int queryBloatedBloomFilter(_long firstHash, _long secondHash);

	_bool BloatedBloomAddToFilter_sorted(_long firstHash, _long secondHash);


	_bool BloatedBloomAddToFilter(_long firstHash, _long secondHash);


	_bool BloatedBloom_Init(_ulong);

	_bool BloatedBloom_Close(void);

	void printBloated(void);

	void printBloatedStat(void);

#endif
