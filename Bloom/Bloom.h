// 
//	Author : vaibhavs@flux.utah.edu
//	Description: header file of Bloated Bloom
//
#ifndef BLOOM_H
#define BLOOM_H
_int queryBloomFilter(_ulong firstHash, _ulong secondHash, _int numberHash);

_bool BloomAddToFilter(_ulong firstHash, _ulong secondHash, _int numberHash);

_bool printBloom();
_bool printBloomInfo();

_bool Bloom_Init(_ulong);
_bool Bloom_Close(void);
#endif
