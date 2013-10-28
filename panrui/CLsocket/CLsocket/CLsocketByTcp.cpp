#include "CLsocketByTcp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>

using namespace std;

unsigned short portbase = 0;
string transport = "tcp";

CLsocketByTcp::CLsocketByTcp():isInit(false){}

CLsocketByTcp::CLsocketByTcp(int fd):isInit(true)
{
	this->fd = fd;
}

CLsocketByTcp::~CLsocketByTcp()
{

}

bool CLsocketByTcp::getPort(unsigned short &net_port,const string & port)
{
	servent 	*pse;
	if(( pse = getservbyname(port.c_str(),transport.c_str())) != 0)
		net_port = htons(ntohs((unsigned short )pse->s_port)+portbase);
	else if((net_port = htons((unsigned short )atoi(port.c_str()))) == 0)
			return true;
	return false;
}

bool CLsocketByTcp::getType(int &type)
{
	type = SOCK_STREAM;
	return false;
}

bool CLsocketByTcp::getProto(protoent *& ppe)
{
	if((ppe = getprotobyname(transport.c_str())) == 0)
		return true;
	return false;
}

bool CLsocketByTcp::startlisten(const int qlen )
{
	if( 0 > bind(fd,(sockaddr *)&sin,sizeof(sin)))
			return true ;
	if(listen(fd,qlen)<0)
			return true ;
	return false ;
}
