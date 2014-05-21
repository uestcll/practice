#ifndef CLEVENT_MANAGER_BY_SELECT_H
#define CLEVENT_MANAGER_BY_SELECT_H

#include "CLEventManager.h"

class CLEventManagerBySelect:public CLEventManager
{
public:

	virtual int StartMainLoop(timeval );

	virtual ~CLEventManagerBySelect();

	virtual int RemoveObserver(int fd);
    virtual int RemoveTimeOut(EventCallBack callback);

	static CLEventManager * GetInstantce();
protected:
	CLEventManagerBySelect();
	
private:

	virtual int SetReasonForCall(int fd,int reasonForCall);

	int m_fdMax;
	fd_set m_wset;
	fd_set m_rset;
	fd_set m_eset;

	void ToDispatchBySet(fd_set fdset);

	CLEventManagerBySelect(const CLEventManagerBySelect &);
	const CLEventManagerBySelect & operator = (const CLEventManagerBySelect &);


};

#endif
