// 
//	Author : vaibhavs@flux.utah.edu
//	Description: header file of Bloated Bloom SORTED
//
#ifndef BLOATED_BLOOM_SORTED_H
#define BLOATED_BLOOM_SORTED_H

	_int queryBloatedBloomSortedFilter(_long firstHash, _long secondHash);


	_bool BloatedBloomSortedAddToFilter(_long firstHash, _long secondHash);


	_bool BloatedBloomSorted_Init(_ulong);

	_bool BloatedBloomSorted_Close(void);

	void printBloatedSorted(void);

	void printBloatedSortedStat(void);

#endif
