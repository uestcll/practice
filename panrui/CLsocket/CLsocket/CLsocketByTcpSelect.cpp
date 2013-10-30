#include "CLsocketByTcpSelect.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int CLsocketByTcpSelect::readLen;

CLsocketByTcpSelect::CLsocketByTcpSelect():CLsocketByTcp()
{}

CLsocketByTcpSelect::CLsocketByTcpSelect(int fd):CLsocketByTcp(fd)
{}

CLsocketByTcpSelect::~CLsocketByTcpSelect()
{}

void CLsocketByTcpSelect::initBeforeLoop()
{
	nfds = getdtablesize();
	FD_ZERO(&afds);
	FD_SET(fd,&afds);
}

void CLsocketByTcpSelect::BecalledAfterGetNewConnection()
{

}

void CLsocketByTcpSelect::selectAndAccept()
{
	try{
		memcpy(&rfds,&afds,sizeof(rfds));
		if(select(nfds,&rfds,(fd_set *)0,(fd_set *)0,wait)<0)
			throw "error happened while selecting";
		if(FD_ISSET(fd,&rfds))
		{	
			int n_fd = accept(fd,(sockaddr *)&rmt_sin,&rmt_len);
			if(n_fd<0)
				throw "error happened while accepting";
			BecalledAfterGetNewConnection();
			FD_SET(n_fd,&afds);
		}
	}catch(string err)
	{
		std::cerr<<err<<endl;
		exit(-1);
	}
}

int CLsocketByTcpSelect::getConnectFd()
{
	static int cur = 0;
	for(;cur<nfds;cur++)
		if(cur!=fd&&FD_ISSET(cur,&rfds))
			return cur;
	cur = 0;
	return -1;	
}

int CLsocketByTcpSelect::send(void *Buf,const int size)
{
	return ::send(fd,Buf,size,0);
}

int CLsocketByTcpSelect::receive(void *Buf)
{
	int cur = 0;
	int add = 0;
	while((add = recv(fd,&(((char *)Buf)[cur]),readLen,0))!=0)
			cur+=add;
	return cur;
}
