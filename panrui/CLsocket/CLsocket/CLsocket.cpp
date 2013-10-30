#include "CLsocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#ifndef INADDR_ANY
#define INADDR_ANY 0xffffffff
#endif

CLsocket::CLsocket():fd(-1),isServer(false ){}
CLsocket::~CLsocket()
{
	if(isServer)
		close(fd);
}

void CLsocket::getSocket(const string & host,const string & port)
{
	hostent 	*phe;
	protoent 	*ppe;

	int 		type;
	memset(&sin,0,sizeof(sin));

	sin.sin_family = AF_INET;
	try{
		if(getPort(sin.sin_port,port))
			throw "error happened while finding port";
		
		if(isServer)
				sin.sin_addr.s_addr = INADDR_ANY;
		else
			if((phe = gethostbyname(host.c_str()))!=0)
				memcpy(&sin.sin_addr,phe->h_addr,phe->h_length);
			else if((sin.sin_addr.s_addr = inet_addr(host.c_str() )) == INADDR_NONE)
				throw "error happened while setting ip";
			
		if(getType(type))
			throw "error happened while getting data type";

		if(getProto(ppe))
			throw "error happened while gettring proto type";

		if(0 > (fd = socket(PF_INET,type,ppe->p_proto)))
			throw "error happened while applying for a socket";
	
	}catch(string err)
	{
		cerr<<err<<endl;
		exit(-1);
	}

}

int CLsocket::connectsocket(const string & host,const string & port)
{
	isServer = false;
	getSocket(host,port);
	try{
		if(0 > connect(fd,(sockaddr *)&sin,sizeof(sin)))
			throw "error happened while connectint to server";
		return fd;
	}catch(string err)
	{
		cerr<<err<<endl;
		exit(0);
	}
}

int CLsocket::passivesocket(const string &port,const int qlen)
{
	isServer = true;
	string addr = "";

	getSocket(addr,port);
	try{
		if(startlisten(qlen))
			throw "error happened while listening port";
		return fd;
	}catch(string err)
	{
		cerr<<err<<endl;
		exit(-1);
	}
}




