#ifndef PB_LOAD
#define PB_LOAD

#include "PBexecute.h"
#include "PBaddNew.h"

#include <fstream>
using namespace std;
class PBload:public PBexecute
{
private:
	ifstream *	istr;
	PBaddNew *	pb_addNew;
	bool analysisPara(string para,string &path);
protected:
public:
	PBload();
	~PBload();
	virtual bool isExecute(string cmd);
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para);
};

#endif