#include "Huffman.h"
#include "Decode.h"
#include "Encode.h"

#include <string.h>
void main(int argc,char * argv[])
{
	if(argc != 4)
	{
		Usage();
		return ;
	}

	if(memcmp(argv[1],"-c",3)==0)
	compression(argv[2],argv[3]);
	else if(memcmp(argv[1],"-u",3)==0)
	decompression(argv[2],argv[3]);
	else 
	Usage();
}