#include "CmdDispatchForHuffman.h"
//#define FOR_DEBUG
int main(int argc,char*argv[])
{
#ifdef FOR_DEBUG
	CmdDispatchForHuffman  compression(4,"test","-c","D:\\dudu.txt","D:\\pp.bin");
	CmdDispatchForHuffman  decompression(4,"test","-d","D:\\pp.bin","D:\\dudu.txt");
#endif

#ifndef FOR_DEBUG
	CmdDispatchForHuffman  action(4,argv[0],argv[1],argv[2],argv[3]);
#endif

	return 0;
}