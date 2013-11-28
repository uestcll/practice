#ifndef CLMsgClass_H
#define CLMsgClass_H
#include <list>
#include <string>
#include <memory>

using namespace std;

class CLMsgElement;
class CLMsgClass
{
public:
	CLMsgClass(bool is_struct);
	~CLMsgClass();

	void addSuperClass(string &superClass);
	CLMsgElement * addMemberVar(CLMsgElement * memberVar);

	list<shared_ptr<CLMsgElement> >::iterator  beginVar(){return m_memberVar.begin();}
	const list<shared_ptr<CLMsgElement> >::iterator  endVar(){return m_memberVar.end();}

	string getSuperClass(){ return m_superClass;}

private:
	const CLMsgClass & operator = (const CLMsgClass &);
	CLMsgClass(const CLMsgClass &);

private:
	bool			m_isStruct;
	bool			m_isVirtualClass;
	string			m_superClass;
	list<shared_ptr<CLMsgElement> >		m_memberVar;
};

#endif