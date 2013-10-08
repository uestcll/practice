#ifndef PB_SAVE_REMOTE
#define PB_SAVE_REMOTE

#include "PBexecute.h"
#include "PBsave.h"
#include "PBTool.h"
using namespace std;

class PBsaveRemote:public PBexecute
{
private:
	PBsave * pb_save;
protected:
public:
	PBsaveRemote();
	~PBsaveRemote();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
};
#endif
