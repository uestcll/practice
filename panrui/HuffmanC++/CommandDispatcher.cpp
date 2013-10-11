#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(unsigned int num):num(num),cmd(NULL)
{

}

CommandDispatcher::~CommandDispatcher()
{
	delete cmd;
}