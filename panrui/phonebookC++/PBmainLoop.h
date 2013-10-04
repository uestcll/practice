#ifndef PB_MAIN_LOOP
#define PB_MAIN_LOOP

#include "PBitem.h"
#include "PBexecute.h"
#include <iostream>
#include <vector>

using namespace std;

class PBadapter;

class PBmainLoop
{
private:
	PBadapter *		pb_adapter;
	vector<PBitem *> pb_item;
	string			curCMD;
	PBexecute * analysisCMD();
	void listenCMD();
	bool dispatchCMD(PBexecute * aimExecute);
protected:

public:
	PBmainLoop(PBadapter * pb_adapter);
	~PBmainLoop();
	void mainloop();
};


#endif