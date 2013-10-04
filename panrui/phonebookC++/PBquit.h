#ifndef PB_QUIT
#define PB_QUIT
#include "PBexecute.h"
class PBquit:public PBexecute
{
private:
protected:
public:
	PBquit();
	~PBquit();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
};


#endif