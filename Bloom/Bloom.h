// 
//	Author : vaibhavs@flux.utah.edu
//	Description: header file of Bloated Bloom
//
#ifndef BLOOM_H
#define BLOOM_H

extern _bool VectorBloom[Index_B];


_int queryBloomFilter(_ulong firstHash, _ulong secondHash, _int numberHash);

_bool BloomAddToFilter(_ulong firstHash, _ulong secondHash, _int numberHash);

_bool printBloom();
_bool printBloomInfo();

#endif
