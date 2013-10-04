#include "PBadapter.h"
#include "PBmainLoop.h"

PBadapter::PBadapter()
{
	this->pb_mainloop = new PBmainLoop(this);
	initRegList();
}

PBadapter::~PBadapter()
{
	delete pb_mainloop;
	uninitRegList();
}

void PBadapter::regSingle(PBexecute * waitForReg)
{
	pb_execute.push_back(waitForReg);
}

void PBadapter::initRegList()
{
	regSingle(new PBaddNew());
	regSingle(new PBshow());
	regSingle(new PBquit());
}

void PBadapter::uninitRegList()
{
	vector<PBexecute *>::iterator it = pb_execute.begin();
	
	while(it != pb_execute.end())
	{
		delete (*it++);
	}

	pb_execute.clear();
}


PBexecute * PBadapter::fdAimExe(string CMD)
{
	vector<PBexecute *>::iterator it = pb_execute.begin();

	while(it != pb_execute.end())
	{
		if((*it)->isExecute(CMD))
		{
			return *it;
		}
		it++;
	}
	return NULL;
}

void PBadapter::start()
{
	pb_mainloop->mainloop();
}



