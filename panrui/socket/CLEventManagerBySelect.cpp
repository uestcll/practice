#include "CLEventManagerBySelect.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

CLEventManagerBySelect::CLEventManagerBySelect():m_fdMax(0)
{
	FD_ZERO(&m_wset);
	FD_ZERO(&m_rset);
	FD_ZERO(&m_eset);
}

CLEventManagerBySelect::~CLEventManagerBySelect()
{
	
}

int CLEventManagerBySelect::StartMainLoop(timeval waitTime)
{
	while(true)
	{
		fd_set wset = m_wset;
		fd_set rset = m_rset;
		fd_set eset = m_eset;

		if(select(m_fdMax+1,&rset,&wset,&eset,&waitTime))
		{
			this->ToDispatchBySet(wset);
			this->ToDispatchBySet(rset);
			this->ToDispatchBySet(eset);
		}
		else
		{
			list<SCallBackAndPara *>::iterator it = m_timeoutTable.begin();
			while(it != m_timeoutTable.end())
			{
				(*it)->callback((*it)->para);
			}
		}
	}
	return 0;
}

int CLEventManagerBySelect::SetReasonForCall(int fd,int reasonForCall)
{
	switch(reasonForCall)
	{
	case CALL_READ:

		FD_SET(fd,&m_rset);	
		break;
	case CALL_WRITE:
		FD_SET(fd,&m_wset); 
		break;

	default:
		FD_SET(fd,&m_eset); 
		break;
	}
	if(fd>m_fdMax)
		m_fdMax = fd;
	return 0;
}

CLEventManager* CLEventManagerBySelect::GetInstantce()
{
	static CLEventManagerBySelect s_cembs;

	return &s_cembs;
}

int CLEventManagerBySelect::RemoveObserver(int fd)
{
	FD_CLR(fd,&m_eset);
    FD_CLR(fd,&m_rset);
	FD_CLR(fd,&m_wset);

	return CLEventManager::RemoveObserver(fd);
}

int CLEventManagerBySelect::RemoveTimeOut(EventCallBack callback)
{
	return CLEventManager::RemoveTimeOut(callback);
}

void CLEventManagerBySelect::ToDispatchBySet(fd_set fdset)
{
	for(int i = 0;i<m_fdMax+1;i++)
	{
		if(FD_ISSET(i,&fdset))
		{
			SCallBackAndPara * ftocall = m_callbackTable.find(i)->second;
			ftocall->callback(ftocall->para);
		}
	}
}


