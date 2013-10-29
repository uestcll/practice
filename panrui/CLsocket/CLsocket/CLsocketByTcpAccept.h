#ifndef _CL_SOCKET_BY_TCP_ACCEPT_
#define _CL_SOCKET_BY_TCP_ACCEPT_
#include "CLsocketByTcp.h"

class CLsocketByTcpAccept:public CLsocketByTcp
{
private:
	sockaddr_in rmt_sin;
	socklen_t 	rmt_addr_len;
public:
	int AcceptRequest();
	CLsocketByTcpAccept();
	CLsocketByTcpAccept(int fd);
	virtual ~CLsocketByTcpAccept();
};

#endif
