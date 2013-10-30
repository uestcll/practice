#ifndef _CL_SOCKET_BY_TCP_ACCEPT_
#define _CL_SOCKET_BY_TCP_ACCEPT_
#include "CLsocketByTcp.h"

class CLsocketByTcpAccept:public CLsocketByTcp
{
private:
	sockaddr_in rmt_sin;
	socklen_t 	rmt_addr_len;

	static const int readLen = 1024;
public:
	int AcceptRequest();
	CLsocketByTcpAccept();
	CLsocketByTcpAccept(int fd);
	virtual ~CLsocketByTcpAccept();
	virtual int send(void * Buf,const int size);
	virtual int receive(void * Buf);
	string getRemotePort();
	string getRemoteAddr();

};

#endif
