#include "CLClassDescribe.h"
#include "CLAbstractType.h"

CLClassDescribe::CLClassDescribe()
{

}

CLClassDescribe::~CLClassDescribe()
{
	list<CLAbstractType *>::iterator it = m_elementList.begin();
	while(it != m_elementList.end() )
	{
		delete (*it);
		it++;
	}
}