#ifndef PB_SHOW
#define PB_SHOW
#include "PBexecute.h"
class PBshow:public PBexecute
{
private:
protected:
public:
	PBshow();
	~PBshow();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);	
};


#endif