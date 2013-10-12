#include "HuffmanAnalysis.h"
#include <cstring>
HuffmanAnalysis::HuffmanAnalysis(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum):CmdAnalysis(retValue,cmd,paraNum)
{
	
}

HuffmanAnalysis::~HuffmanAnalysis()
{

}

void HuffmanAnalysis::startAnalysis()
{

	if(paraNum != 4)
	{
		retValue = Usage;
		return ;
	}
    if(strcmp((char *)cmd[1],"-c")==0)
        retValue = Compress;
	else if(strcmp((char *)cmd[1],"-d")==0)
		retValue = Decompress;
	else
		retValue = Usage;
}
