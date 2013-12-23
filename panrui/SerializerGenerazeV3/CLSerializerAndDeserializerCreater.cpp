#include "CLSerializerAndDeserializerCreater.h"

#include "CLAbstractMethod.h"
#include "CLAbstractType.h"
#include "CLBuiltInMethod.h"
#include "CLBuiltInType.h"
#include "CLStringMethod.h"
#include "CLStringType.h"
#include "CLUserDefMethod.h"
#include "CLUserDefType.h"

#include "CLClassInterpreter.h"
#include "CLClassDescribe.h"

#include "CLSetOffset.h"
#include "CLFileTraverser.h"

#include "CLDeserializerCreater.h"
#include "CLSerializerCreater.h"

#include <algorithm>

CLSerializerAndDeserializerCreater::CLSerializerAndDeserializerCreater(const char * path):
m_fileList(NULL),m_directory(path),m_needdestory(false)
{
	
}

CLSerializerAndDeserializerCreater::~CLSerializerAndDeserializerCreater()
{
	if(m_needdestory)
		destroyEnvironment();

	if(m_fileList != NULL)
		delete m_fileList;
}

void CLSerializerAndDeserializerCreater::initEnvironment()
{
	m_classMethodMap[ typeid(CLStringType).name() ] = new CLBuiltInMethod();
	m_classMethodMap[ typeid(CLStringType).name() ] = new CLStringMethod();
	m_classMethodMap[ typeid(CLUserDefType).name() ] = new CLUserDefMethod();

	CLClassInterpreter::s_ElementGeterFunctionMap["bool"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["char"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["uint8_t"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["uchar"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["short"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["uint16_t"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["int"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["uin32_t"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["float"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["long"] = CLClassInterpreter::getBuiltIn;
	CLClassInterpreter::s_ElementGeterFunctionMap["double"] = CLClassInterpreter::getBuiltIn;

	CLClassInterpreter::s_ElementGeterFunctionMap["string"] = CLClassInterpreter::getString;
	CLClassInterpreter::s_ElementGeterFunctionMap["UserDef"] = CLClassInterpreter::getUserDef;

	m_needdestory = true;
}

void CLSerializerAndDeserializerCreater::destroyEnvironment()
{
	map<string , CLAbstractMethod *>::iterator it = m_classMethodMap.begin();

	while(it != m_classMethodMap.end())
	{
		delete (it->second);
		it++;
	}

	map< string , CLAbstractMethod *>::iterator itd = m_classMethodMap.begin();
	while(it != m_classMethodMap.end())
	{
		delete it->second;
		it++;
	}

	m_needdestory = false;
}

void CLSerializerAndDeserializerCreater::creatSerializerAndDeserializer()
{
	traverDirectory();

	list<string >::iterator it = m_fileList->begin();
	while(it != m_fileList->end())
	{
		CLClassInterpreter interpreter;
		CLClassDescribe * ret = interpreter.loadClassByFilename(*it);

		if(ret->m_featrueSet.find(SERIAL_FEATURE) != ret->m_featrueSet.end())
			m_serializeList.push_back(ret->m_classname);

		m_classDescribeMap[ret->m_classname] = ret;
		
		it++;
	}

	recheckSerialList();

	list<string >::iterator serialIt = m_serializeList.begin();
	while(serialIt != m_serializeList.end())
	{
		setOffset(m_classDescribeMap.find(*serialIt)->second);
	}

	creatSerializer();

	creatDeserializer();

}

void CLSerializerAndDeserializerCreater::recheckSerialList()
{
	list<string >::iterator it = m_serializeList.begin();

	while(it != m_serializeList.end() )
	{
		CLClassDescribe * t_serialClass = m_classDescribeMap.find(*it)->second;
		list<CLAbstractType * >::iterator t_typeIt = t_serialClass->m_elementList.begin();

		while(t_typeIt != t_serialClass->m_elementList.end() )
		{
			if(typeid(*t_typeIt) == typeid(CLUserDefType))
			{
				if(find(m_serializeList.begin(),m_serializeList.end(),(*t_typeIt)->getVarName()) != m_serializeList.end())
				{
					m_serializeList.push_back((*t_typeIt)->getVarName() );

				}

			}

			t_typeIt++;
		}

		it++;
	}

}

void CLSerializerAndDeserializerCreater::traverDirectory()
{
	CLFileTraverser  t_traverser;

	m_fileList = t_traverser.TraversingFile(m_directory);
}

void CLSerializerAndDeserializerCreater::setOffset(CLClassDescribe * in)
{
	CLSetOffset t_setoffset;
	
	t_setoffset.startWork(in,this);
}

void CLSerializerAndDeserializerCreater::creatSerializer()
{
	list<string >::iterator it = m_serializeList.begin();

	CLSerializerCreater t_serializerCreater;

	while(it != m_serializeList.end() )
	{
		t_serializerCreater.run(m_classDescribeMap.find(*it)->second,&m_classMethodMap);

		it++;
	}

}

void CLSerializerAndDeserializerCreater::creatDeserializer()
{
	list<string >::iterator it = m_serializeList.begin();

	CLDeserializerCreater t_deserializerCreater;

	while(it != m_serializeList.end() )
	{
		t_deserializerCreater.run(m_classDescribeMap.find(*it)->second,&m_classMethodMap);

		it++;
	}

}
