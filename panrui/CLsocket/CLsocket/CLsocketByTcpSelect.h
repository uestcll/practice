#ifndef _CL_SOCKET_BY_TCP_ACCEPT_
#define _cL_SOCKET_BY_TCP_ACCEPT_
#include "CLsocketByTcp.h"
#include <sys/time.h>

class CLsocketByTcpSelect:public CLsocketByTcp
{
protected:
	fd_set 	rfds;
	fd_set  afds;
	timeval * wait;

	int 	nfds;
	sockaddr_in rmt_sin;
	socklen_t 	rmt_len;

	const static int readLen = 1024;
public:
	CLsocketByTcpSelect();
	CLsocketByTcpSelect(int fd);
	virtual ~CLsocketByTcpSelect();
	virtual int send(void *Buf,const int size);
	virtual int receive(void * Buf);
	virtual void BecalledAfterGetNewConnection();


	void setWaitTime(timeval * in_time);
	void initBeforeLoop();
	void selectAndAccept();
	int  getConnectFd();
	
};

#endif
