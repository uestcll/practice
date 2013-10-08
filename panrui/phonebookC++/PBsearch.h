#ifndef PB_SEARCH
#define PB_SEARCH
#include "PBexecute.h"
#include "PBshow.h"
#include "PBTool.h"
class PBsearch:public PBexecute
{
private:
protected:
public:
	PBsearch();
	~PBsearch();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);

};

#endif
