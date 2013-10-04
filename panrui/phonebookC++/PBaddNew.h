#ifndef PB_ADD_NEW
#define PB_ADD_NEW
#include "PBexecute.h"
class PBaddNew:public PBexecute
{
private:
	void analysisPara(string para,string &name,string &num);
protected:
public:
	PBaddNew();
	~PBaddNew();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
	
};
#endif 