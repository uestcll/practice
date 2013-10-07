#include "Encode.h"

char EncodeToNewFile(char * source,char * dest,hTree * h_map)
{
	FILE * rf = fopen(source,"rb");
	if(rf == NULL)
		return -1;

	FILE * wf = fopen(dest,"wb");
	if(wf == NULL)
		return -1;

	fseek(rf,0,SEEK_END);
	long long int length = ftell(rf);
	fseek(rf,0,SEEK_SET);

	BUFFER * buffer = InitBuffer();
	for(int i =0;i<length ;i++)
	{
		unsigned char in = fgetc(rf);
		writeTo(in,buffer,h_map,wf);
	}

	char leftBit = 8-buffer->ext_bit;

	desBuffer(buffer,wf);
	fclose(rf);
	fclose(wf);
	return leftBit;
}

BUFFER * InitBuffer()
{
	BUFFER * buffer = (BUFFER *)calloc(1,sizeof(BUFFER));
	if(buffer == NULL)
		return NULL;
	return buffer;
}

void desBuffer(BUFFER * buffer,FILE * wf)
{
	if(buffer->ext_bit == 0)
	{
		fwrite(buffer->preBuf,1,buffer->pBlen,wf);
	}
	else
		fwrite(buffer->preBuf,1,buffer->pBlen+1,wf);
	free(buffer);
}

void writeTo(unsigned char in,BUFFER * buffer,hTree * h_map,FILE *wf)
{
	int bitlen = h_map[in].bit;
	unsigned char tmp = 1;
	while(bitlen)
	{ 
		tmp<<=((bitlen-1)%8);
		tmp&=h_map[in].hfCode[31-(bitlen-1)/8];
		tmp>>=((bitlen-1)%8);
		bitlen--;

		tmp<<=7-(buffer->ext_bit);
		buffer->preBuf[buffer->pBlen]^=tmp;
		
		if(buffer->ext_bit == 7)
		{
			buffer->pBlen++;
			buffer->ext_bit=0;
		}else	buffer->ext_bit++;
		
		tmp = 1;
	}
	if(buffer->pBlen>=BUFF/2)
	{
		fwrite(buffer->preBuf,1,32,wf);
		
		memcpy(buffer->preBuf,&buffer->preBuf[32],32);
		memset(&buffer->preBuf[32],0,32);
		
		buffer->pBlen-=32;
	}
}

void	compression(char * source,char * dest)
{
	hTree * pp = initHTreeMap();
	hTree * ss = loadFile(pp,source);
	
	saveHuffmanToFile(ss,EncodeToNewFile(source,dest,pp));
	destoryHTreeMap(pp,ss);
}
