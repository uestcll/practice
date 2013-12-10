#ifndef CLMsgClassManager_H
#define CLMsgClassManager_H

#include <map>
#include <list> 
#include <memory>
using namespace std;

class CLMsgClass;

class CLMsgClassManager
{
public:
	CLMsgClassManager();
	~CLMsgClassManager();

	CLMsgClass* findClass(string classname);

	list<string>::iterator  serialingNameMapBegin(){ return serialingNameMap.begin();};
	const list<string>::iterator  serialingNameMapEnd(){ return serialingNameMap.end();};

	CLMsgClass *classRegister(string classname,bool is_needserial,bool is_struct);
public:
	void	loadAlltheFile(string *filelist,int strNum);

private:
	const CLMsgClassManager & operator= (const CLMsgClassManager &);
	CLMsgClassManager(const CLMsgClassManager &);

private:
	list<string> serialingNameMap;
	map<string,shared_ptr<CLMsgClass > >	classMap;
	
};

#endif