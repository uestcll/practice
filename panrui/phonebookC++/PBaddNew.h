#ifndef PB_ADD_NEW
#define PB_ADD_NEW
#include "PBexecute.h"
#include "PBTool.h"
class PBaddNew:public PBexecute
{
private:
protected:
public:
	PBaddNew();
	~PBaddNew();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
	
};
#endif 
