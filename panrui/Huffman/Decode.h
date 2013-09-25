#ifndef		_DECODE_
#define		_DECODE_

#include "Huffman.h"

void	DecodeFromFile(char * source,char * dest,hTree * h_tree,char leftBit);
unsigned char	Decode(FILE * rf,hTree * h_tree,char *signal,unsigned long length,char leftBit);




#endif