#ifndef CLMsgElementMap_H
#define CLMsgElementMap_H

#include <map>

using namespace std;
class CLMsgElement;
class CLMsgClassManager;


class CLMsgElementMap
{
public:
	~CLMsgElementMap();
	static CLMsgElementMap * getInstance();
	CLMsgElement * initNewElement(string &sentence,CLMsgClassManager * pmng);
private:
	CLMsgElementMap();
	void registMap();
	const CLMsgElementMap & operator = (const CLMsgElementMap &);
	CLMsgElementMap(CLMsgElementMap &);
	
	map<string ,CLMsgElement * (*)(CLMsgClassManager * )>  f_map;
	void getNextItem(string &tmp,string &out,bool if_reset);
	
private:
	static CLMsgElement * initBasic(CLMsgClassManager *);
	static CLMsgElement * initString(CLMsgClassManager *);
	static CLMsgElement * initUser(CLMsgClassManager *);
};
#endif