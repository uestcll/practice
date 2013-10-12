#include "CommandDispatcher.h"
#include "HuffmanAnalysis.h"
#include "HuffmanExecute.h"

CommandDispatcher::CommandDispatcher(unsigned int paraNum,...):cmd(NULL),
		paraNum(paraNum),analysisResult(-1),doExecute(NULL),doAnalysis(NULL)
{
	va_list ap;
	va_start(ap,paraNum);
	if(paraNum != 0)
			cmd = new unsigned char *[paraNum];
	for(unsigned int i = 0;i<paraNum;i++)
	{
		cmd[i] = va_arg(ap,unsigned char *);	
	}
	va_end(ap);
}

CommandDispatcher::~CommandDispatcher()
{
	delete cmd;
	if(doExecute != NULL)
		delete doExecute;
	if(doAnalysis != NULL)
		delete doAnalysis;
}

void CommandDispatcher::startDispatch()
{
	doAnalysis = new HuffmanAnalysis(this->analysisResult,this->cmd,this->paraNum);
	doAnalysis->startAnalysis();
	doExecute = new HuffmanExecute(this->analysisResult,this->cmd,this->paraNum);
	doExecute->startExecute();
}
