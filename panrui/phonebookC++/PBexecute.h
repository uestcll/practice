#ifndef PB_EXECUTE
#define PB_EXECUTE

#include "PBitem.h"
#include "PBusage.h"
#include <vector>
#include <string>
#include <iostream>

#define CMD_LEN 3
#define DEFAULT_PATH "./phonebook.txt"

using namespace std;

class PBexecute
{
private:

protected:
public:
	PBexecute();
	~PBexecute();
	virtual bool isExecute(string cmd) = 0;
	virtual bool executeCMD(vector<PBitem *> &pb_item,string para) = 0;
};


#endif 
