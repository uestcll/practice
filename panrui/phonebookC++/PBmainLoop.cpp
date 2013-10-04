#include "PBmainLoop.h"
#include "PBadapter.h"

PBmainLoop::PBmainLoop(PBadapter * pb_adapter)
{
	this->pb_adapter = pb_adapter;
}

PBmainLoop::~PBmainLoop()
{
	vector<PBitem *>::iterator it= pb_item.begin();
	while(it != pb_item.end())
	{
		delete (*it++);
	}
	pb_item.clear();
}

PBexecute * PBmainLoop::analysisCMD()
{
	return pb_adapter->fdAimExe(curCMD);
}

void PBmainLoop::listenCMD()
{
	getline(cin,curCMD,'\n');
}

bool PBmainLoop::dispatchCMD(PBexecute * aimExecute )
{
	return aimExecute->executeCMD(pb_item,curCMD.substr(CMD_LEN,curCMD.length()-CMD_LEN));
}

void PBmainLoop::mainloop()
{
	do
	{
		cout<<'#';
		curCMD.clear();
		listenCMD();
	
	}while(dispatchCMD(analysisCMD()));
}
