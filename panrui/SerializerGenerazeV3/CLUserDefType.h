#ifndef CLUserDefType_H
#define CLUserDefType_H

#include "CLAbstractType.h"
#include <string>

using namespace std;

class CLUserDefType:public CLAbstractType
{
public:

	CLUserDefType();
	virtual ~CLUserDefType();
	virtual void analysisFromStatement(string  & );

	const string & getUserDefName(){ return m_userdef_name;}

private:

	CLUserDefType(const CLUserDefType &);
	const CLUserDefType & operator = (const CLUserDefType &);

private:

	string m_userdef_name;


};

#endif