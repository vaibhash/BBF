// 
//	Author : vaibhavs@flux.utah.edu
//	Description: header file of Bloated Bloom
//
#ifndef BLOATED_BLOOM_H
#define BLOATED_BLOOM_H

extern _byte VectorBloatedBloom[Index_BB/2+Index_BB%2];



_int queryBloatedBloomFilter_sorted(_long firstHash, _long secondHash);
_int queryBloatedBloomFilter(_long firstHash, _long secondHash);

_bool BloatedBloomAddToFilter_sorted(_long firstHash, _long secondHash);


_bool BloatedBloomAddToFilter(_long firstHash, _long secondHash);

void printBloated(void);

void printBloatedStat(void);


		
//
//  these function counts the number of collioson 
//  in the hash values
//  
		int AddList(_ulong hashValue, node** headnode);
		void PrintList(node* headnode);
		void DeleteList(node* headnode);

#endif
