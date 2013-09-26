#ifndef		_ENCODE_
#define		_ENCODE_
#include "Huffman.h"

#define BUFF 64

struct BUFFER
{
	char preBuf[BUFF];
	unsigned int  pBlen;
	unsigned char ext_bit;
};

char	EncodeToNewFile(char * source,char * dest,hTree * h_map);
BUFFER *InitBuffer();
void	writeTo(unsigned char in,BUFFER * buffer,hTree * h_map,FILE * wf);
void	desBuffer(BUFFER * buffer,FILE * wf);

void	compression(char * source,char * dest);


#endif