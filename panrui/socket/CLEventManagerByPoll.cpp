#include "CLEventManagerByPoll.h"

CLEventManagerByPoll::CLEventManagerByPoll(int FDMAX):m_pfdAry(new pollfd[FDMAX]),m_fdMax(FDMAX)
{
	for(int i = 0;i<FDMAX ;i++)
	{
		m_pfdAry[i].fd = -1;
		m_pfdAry[i].events = 0;
		m_pfdAry[i].revents = 0;
	}
}

CLEventManagerByPoll::~CLEventManagerByPoll()
{
	delete m_pfdAry;
}

CLEventManager * CLEventManagerByPoll::GetInstance(int FDMAX)
{
	static CLEventManagerByPoll cembp(FDMAX);
	return &cembp;
}

int CLEventManagerByPoll::StartMainLoop(timeval time )
{
	int timeout = time.tv_usec/1000+time.tv_sec*1000;

	while(true )
	{
		poll(m_pfdAry,m_fdMax,timeout);
	
		for(int i = 0;i<m_fdMax;i++)
		{
			if(m_pfdAry[i].revents&m_pfdAry[i].events)
			{
				SCallBackAndPara * pscbp = m_callbackTable.find(m_pfdAry[i].fd)->second;
				pscbp->callback(pscbp->para);	
			}
		}
	}

	return 0;
}

int CLEventManagerByPoll::RemoveObserver(int fd)
{
	for(int i = 0;i<m_fdMax;i++)
	{
		if(m_pfdAry[i].fd == fd)
		{
			m_pfdAry[i].fd = -1;
			m_pfdAry[i].events = 0;
			m_pfdAry[i].revents = 0;
		}
	}
	
	return CLEventManager::RemoveObserver(fd);
}

int CLEventManagerByPoll::RemoveTimeOut(EventCallBack callback)
{
	return CLEventManager::RemoveTimeOut(callback);	
}

int CLEventManagerByPoll::SetReasonForCall(int fd,int reasonForCall)
{
	for(int i = 0;i<m_fdMax ;i++)
	{
		if(m_pfdAry[i].fd == -1)
		{
			m_pfdAry[i].fd = fd;
			switch(reasonForCall)
			{
			case CALL_READ:
				m_pfdAry[i].events |=POLLIN;
				return 0;
			case CALL_WRITE:
				m_pfdAry[i].events |=POLLOUT;
				return 0;
			default:
				return 0;
			}
		}
	}
	return -1;	
}


