#include "CLsocketByTcpAccept.h"

#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

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

string CLsocketByTcpAccept::getRemoteAddr()
{
	string ret = inet_ntoa(rmt_sin.sin_addr);
	return ret;
}

string CLsocketByTcpAccept::getRemotePort()
{
	char tmp[6] = {0};
	sprintf(tmp,"%d",rmt_sin.sin_port);
	string ret = tmp;
	return ret;
}


