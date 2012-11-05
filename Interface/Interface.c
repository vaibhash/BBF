// 
//	Author : vaibhavs@flux.utah.edu
//	Description: Definitions for Interfaces for Bloom
//

/*
g++ Interface.c ../RollOverHash/RollOverHash.o ../ReadHaystack/ReadHaystack.o ../ReadNeedleToBloom/ReadNeedleToBloom.o ../BloatedBloom/BloatedBloom.o 

*/


#include "../ReadNeedleToBloom/ReadNeedleToBloom.h"
#include "../ReadHaystack/ReadHaystack.h"
#include "../Bloom/Bloom.h"
#include "../BloatedBloom/BloatedBloom.h"
#include "../Input/Input.h"



_int main()
{
	int windowSize = window_size;
	//NeedleHaystack("./Input/needle_big_set","/Input/haystack",windowSize);
	//printBloom();
	ReadNeedleFileToBloom("./Input/needle_8000",windowSize,num_hash);
	printBloomInfo();
	//printArray();
	ReadHayStackBloom("./Input/haystack",windowSize,num_hash);
	//printBloated();
	ReadNeedleFileToBloatedBloom("./Input/needle_8000",windowSize);

	printBloatedStat();
	//printBloom();
	//printBloated();
	//printArray();
	ReadHayStack("./Input/haystack",windowSize);
}
