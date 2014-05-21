#ifndef CLEVENT_MANAGER_H
#define CLEVENT_MANAGER_H


#include "CLSocketPack.h"
#include <map>
#include <list>

using namespace std;

#define CALL_EXCEPT	(-1)
#define CALL_WRITE	(-2)
#define CALL_READ	(-3)

typedef void * ( *EventCallBack)(void *);

struct SCallBackAndPara
{
	EventCallBack callback;
	void * para;
};


class CLEventManager
{
public:

	virtual	~CLEventManager();

	virtual int StartMainLoop(timeval ) = 0; 
	
	int RegistObserver(int fd,EventCallBack callback, void * para,int ReasonForCall);
	virtual int RemoveObserver(int fd);

	int RegistTimeOut(EventCallBack callback,void * para);
	virtual int RemoveTimeOut(EventCallBack callback);


private:

	virtual int SetReasonForCall(int fd,int ReasonForCall) = 0;

protected:

	map<int ,SCallBackAndPara *> m_callbackTable;
	list<SCallBackAndPara *> m_timeoutTable;

	CLEventManager();

private:
	CLEventManager(const CLEventManager &);
	const CLEventManager & operator = (const CLEventManager &);
};

#endif
