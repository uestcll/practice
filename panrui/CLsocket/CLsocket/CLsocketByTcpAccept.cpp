#include "CLsocketByTcpAccept.h"

#include <sys/types.h>
#include <sys/socket.h> 

CLsocketByTcpAccept::CLsocketByTcpAccept()
{}

CLsocketByTcpAccept::CLsocketByTcpAccept(int fd):CLsocketByTcp(fd)
{}

CLsocketByTcpAccept::~CLsocketByTcpAccept()
{}

int CLsocketByTcpAccept::AcceptRequest()
{
	return accept(fd,(sockaddr *)&rmt_sin,&rmt_addr_len);
}
