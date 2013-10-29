#include "CLsocketByTcpAccept.h"

#include <sys/types.h>
#include <sys/socket.h> 

const int CLsocketByTcpAccept::readLen;

CLsocketByTcpAccept::CLsocketByTcpAccept():CLsocketByTcp()
{}

CLsocketByTcpAccept::CLsocketByTcpAccept(int fd):CLsocketByTcp(fd)
{}

CLsocketByTcpAccept::~CLsocketByTcpAccept()
{}

int CLsocketByTcpAccept::AcceptRequest()
{
	return accept(fd,(sockaddr *)&rmt_sin,&rmt_addr_len);
}

int CLsocketByTcpAccept::send(void * Buf,const int size )
{
	return ::send(fd,Buf,size,0);	
}

int CLsocketByTcpAccept::receive(void * Buf)
{
	
	int cur = 0;
	int add = 0;
	
	while((add = recv(fd,&(((char *)Buf)[cur]),readLen,0)) != 0)
	{
		cur+= add;
	}
	return cur;
}
