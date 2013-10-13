#include "CommandDispatcher.h"
#define FOR_DEBUG
int main(int argc,char*argv[])
{
#ifdef FOR_DEBUG
	CommandDispatcher  compression(4,"test","-c","D:\\dudu.txt","D:\\pp.bin");
	compression.startDispatch();
	CommandDispatcher  decompression(4,"test","-d","D:\\pp.bin","D:\\boom.txt");
	decompression.startDispatch();
#endif

#ifndef FOR_DEBUG
	if(argc < 4)
		return 0;
	CommandDispatcher  action(4,argv[0],argv[1],argv[2],argv[3]);
	action.startDispatch();
#endif

	return 0;
}