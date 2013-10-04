#ifndef PB_ADAPTER
#define PB_ADAPTER

#include "PBexecute.h"
#include "PBquit.h"
#include "PBaddNew.h"
#include "PBshow.h"

#include <vector>
#include <string>



using namespace std;

class PBmainLoop;

class PBadapter{
private:
	vector<PBexecute *> pb_execute;	
	PBmainLoop * pb_mainloop;

	void regSingle(PBexecute * waitForReg);
	void initRegList();
	void uninitRegList();

protected:

public:
	PBadapter();
	~PBadapter();
	PBexecute * fdAimExe(string CMD);
	void start();

};


#endif 
