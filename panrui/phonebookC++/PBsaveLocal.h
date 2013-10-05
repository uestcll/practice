#ifndef PB_SAVE_LOCAL
#define PB_SAVE_LOCAL

#include "PBexecute.h"
#include "PBsave.h"

using namespace std;

class PBsaveLocal:public PBexecute
{
private:
	PBsave * pb_save;
protected:
public:
	PBsaveLocal();
	~PBsaveLocal();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);

};

#endif