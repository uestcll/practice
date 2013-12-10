#ifndef CLMsgClass_H
#define CLMsgClass_H
#include <list>
#include <string>
#include <memory>

using namespace std;

class CLMsgElement;

struct offset
{
	unsigned long from_start;
	unsigned long max_unit;
	const offset & operator += (const offset & another);
};
class CLMsgClassManager;
class CLOffsetSeter;
class CLMsgClass
{
public:
	friend CLOffsetSeter;
	CLMsgClass(bool is_struct,CLMsgClassManager * p_mng);
	~CLMsgClass();

	void addSuperClass(string &superClass);
	CLMsgElement * addMemberVar(CLMsgElement * memberVar);

	list<shared_ptr<CLMsgElement> >::iterator  beginVar(){return m_memberVar.begin();}
	const list<shared_ptr<CLMsgElement> >::iterator  endVar(){return m_memberVar.end();}

	string getSuperClass(){ return m_superClass;}
	void setVirtualClass();

	offset setOffset();
	unsigned long getOffsetByName();
	bool	getVirtualClassFlag(){	return m_isVirtualClass;}

private:
	const CLMsgClass & operator = (const CLMsgClass &);
	CLMsgClass(const CLMsgClass &);

private:
	bool			m_isStruct;
	bool			m_isVirtualClass;
	string			m_superClass;
	CLMsgClassManager * m_pmng;
	list<shared_ptr<CLMsgElement> >		m_memberVar;
};

#endif