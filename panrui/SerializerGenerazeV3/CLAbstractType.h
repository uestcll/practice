#ifndef CLAbstractType_H
#define CLAbstractType_H

#include <string>

using namespace std;

class CLAbstractType
{
public:

	CLAbstractType();
	virtual ~CLAbstractType();

	virtual void analysisFromStatement(string  & ) = 0;

	void setOff(int v_off ){ m_off = v_off;}
	int getOff(){	return m_off;}

	bool getPtrFlag(){	return m_isPtr;}
	bool getArrFlag(){	return m_isArray;}
	
	int  getTypeLen(){	return m_isPtr?8:m_type_len;}

	int  getArrSize(){	return m_arraySize;}

	const string & getVarName(){	return m_var_name;}

	int m_type_len;

protected:

	string m_var_name;

	bool m_isPtr;
	bool m_isArray;

	int m_arraySize;
	int m_off;

	void getNextItem(string &tmp,string &out,bool if_reset);

private:

	CLAbstractType(const CLAbstractType &);
	const CLAbstractType & operator = (const CLAbstractType &);
};

#endif