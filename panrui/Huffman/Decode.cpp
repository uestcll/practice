#include "Decode.h"
void DecodeFromFile(char * source,char * dest,hTree * h_tree,char leftBit)
{
	FILE * rf = fopen(source,"rb");
	if(rf == NULL)
		return;

	FILE * wf = fopen(dest,"wb");
	if(wf == NULL)
		return;
	fseek(rf,0,SEEK_END);
	unsigned long length = ftell(rf);
	fseek(rf,0,SEEK_SET);
	char signal = 1;
	while(signal)
	{
		unsigned char in = Decode(rf,h_tree,&signal,length,leftBit);
		if(signal)
		fwrite(&in,1,1,wf);
	}
	fclose(rf);
	fclose(wf);

}
unsigned char	Decode(FILE * rf,hTree * h_tree,char *signal,unsigned long length,char leftBit)
{
	static long long step =0;
	static unsigned char code = 0;
	static bool readFlag = 1;

	if(length*8 < step+leftBit)
	{
		*signal = 0;
		return 0;
	}

	if(step%8 == 0&&readFlag)
	{
		fread(&code,1,1,rf);
	}
	
	unsigned char TMP = 0x80;
	TMP>>=step%8;
	TMP&=code;
	step++;

	readFlag = 1;

	if(TMP==0&&h_tree->left!=NULL)
	{
		return Decode(rf,h_tree->left,signal,length,leftBit);
	}
	else if(TMP!=0&&h_tree->right!=NULL)
	{
		return Decode(rf,h_tree->right,signal,length,leftBit);
	}
	else
	{
		step--;
		readFlag = 0;
		return h_tree->value;
	}


}

void	decompression(char * source,char *dest)
{
	char leftBit = 0;
	hTree *sp = loadHuffmanFromFile(&leftBit);
	DecodeFromFile(source,dest,sp,leftBit);
	destoryLoadTree(sp);	
}