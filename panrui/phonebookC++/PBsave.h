#ifndef PB_SAVE
#define PB_SAVE

#include <vector>
#include <string>
#include <fstream>
#include "PBitem.h"
using namespace std;


class PBsave
{
private:
	ofstream *	ostr;
	string getNewString(vector<PBitem *>::iterator &it);
protected:
public:
	PBsave();
	~PBsave();
	void doSave(string path,vector<PBitem *> &pb_item);

};
#endif