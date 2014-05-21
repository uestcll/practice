#include "CLEventManager.h"

CLEventManager::CLEventManager()
{
	
}

CLEventManager::~CLEventManager()
{
	if(m_timeoutTable.size() != 0)
	{
		list<SCallBackAndPara *>::iterator it = m_timeoutTable.begin();
		while(it != m_timeoutTable.end())
		{
			delete *it;
			it++;
		}
	}
	
	if(m_callbackTable.size() != 0)
	{
	
		map<int, SCallBackAndPara *>::iterator it = m_callbackTable.begin();
		while(it != m_callbackTable.end())
		{
			delete it->second;
			it++;
		}
	}
}

int CLEventManager::RegistTimeOut(EventCallBack  callback,void * para)
{
	SCallBackAndPara * s_cbp = new SCallBackAndPara;
	s_cbp->callback = callback;
	s_cbp->para = para;
	
	this->m_timeoutTable.push_back(s_cbp);

	return 0;
}

int CLEventManager::RegistObserver(int fd, EventCallBack callback, void * para, int ReasonForCall)
{
	SCallBackAndPara * s_cbp = new SCallBackAndPara;
	s_cbp->callback = callback;
	s_cbp->para = para;
	this->SetReasonForCall(fd, ReasonForCall);
	
	this->m_callbackTable[fd] = s_cbp;

	return 0;
}

int CLEventManager::RemoveTimeOut(EventCallBack callback)
{
	list<SCallBackAndPara *>::iterator it = m_timeoutTable.begin();
	while(it != m_timeoutTable.end())
	{
		if((*it)->callback == callback)
		{
			delete *it;

			m_timeoutTable.erase(it);
			return 0;
		}

		it++;
	}

	return -1;
}

int CLEventManager::RemoveObserver(int fd)
{
	map<int , SCallBackAndPara *>::iterator it = m_callbackTable.find(fd);
	if(it == m_callbackTable.end())
	{
		return -1;
	}
	else
	{
		delete it->second;
		m_callbackTable.erase(it);

		return 0;
	}
}
