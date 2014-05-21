#ifndef CLEVENT_MANAGER_BY_POLL_H
#define CLEVENT_MANAGER_BY_POLL_H
#include "CLEventManager.h"
#include <poll.h>

class CLEventManagerByPoll:public CLEventManager
{
public:
	virtual int StartMainLoop(timeval);
	virtual ~CLEventManagerByPoll();

	virtual int RemoveObserver(int fd);
	virtual int RemoveTimeOut(EventCallBack callback);

	static CLEventManager * GetInstance(int FDMAX);

protected:
	
	CLEventManagerByPoll(int FDMAX);
	
private:
	
	virtual int SetReasonForCall(int fd,int reasonForCall);
	
	pollfd * m_pfdAry;
	int		 m_fdMax;

	CLEventManagerByPoll(const CLEventManagerByPoll &);
	const CLEventManagerByPoll & operator = (const CLEventManagerByPoll &);
	
};


#endif
