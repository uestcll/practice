#ifndef PB_SAVE_REMOTE
#define PB_SAVE_REMOTE

#include "PBexecute.h"
#include "PBsave.h"

using namespace std;

class PBsaveRemote:public PBexecute
{
private:
	PBsave * pb_save;
	bool analysisPara(string para,string &path);
protected:
public:
	PBsaveRemote();
	~PBsaveRemote();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
};
#endif