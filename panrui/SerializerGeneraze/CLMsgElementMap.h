#ifndef CLMsgElementMap_H
#define CLMsgElementMap_H

#include <map>

using namespace std;
class CLMsgElement;
class CLMsgElementMap
{
public:
	~CLMsgElementMap();
	static CLMsgElementMap * getInstance();
	CLMsgElement * initNewElement(string &sentence);
private:
	CLMsgElementMap();
	void registMap();
	const CLMsgElementMap & operator = (const CLMsgElementMap &);
	CLMsgElementMap(CLMsgElementMap &);
	
	map<string ,CLMsgElement * (*)()>  f_map;
	void getNextItem(string &tmp,string &out,bool if_reset);
	
private:
	static CLMsgElement * initBasic();
	static CLMsgElement * initPointer();
	static CLMsgElement * initString();
	static CLMsgElement * initUser();
};
#endif