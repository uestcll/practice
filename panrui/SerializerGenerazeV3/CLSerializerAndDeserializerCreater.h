#ifndef CLSerializerAndDeserializerCreater_H
#define CLSerializerAndDeserializerCreater_H

#include <list>
#include <string>
#include <map>

using namespace std;

class CLClassDescribe;
class CLAbstractMethod;


class CLSerializerAndDeserializerCreater
{
public:

	CLSerializerAndDeserializerCreater(const char * );
	~CLSerializerAndDeserializerCreater();

	void initEnvironment();
	void creatSerializerAndDeserializer();
	void destroyEnvironment();
	
	map<string ,CLClassDescribe *> m_classDescribeMap;

private:
	
	CLSerializerAndDeserializerCreater(const CLSerializerAndDeserializerCreater & );
	const CLSerializerAndDeserializerCreater & operator = (const CLSerializerAndDeserializerCreater & );

private:

	list<string >	m_serializeList;

	list<string >  * m_fileList;
	string	m_directory;

	map< string , CLAbstractMethod *>  m_classMethodMap;

	bool m_needdestory;

	void recheckSerialList();
	void traverDirectory();
	void creatSerializer();
	void creatDeserializer();

	void setOffset(CLClassDescribe * );
	
};

#endif