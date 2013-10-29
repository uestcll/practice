#include "CLsocketByUdp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>

using namespace std;

string transport = "udp";
unsigned short portbase = 0;
CLsocketByUdp::CLsocketByUdp():isInit(false)
{

}

CLsocketByUdp::CLsocketByUdp(int fd):isInit(true)
{
	this->fd = fd;
}

CLsocketByUdp::~CLsocketByUdp()
{

}

bool CLsocketByUdp::getPort(unsigned short &net_port,const string & port)
{
	servent		*pse;
	
	if(( pse = getservbyname(port.c_str(),transport.c_str())) != 0)
		net_port = htons(ntohs((unsigned short )pse->s_port)+portbase);
	else if( (net_port = htons((unsigned short )atoi(port.c_str()))) ==0)
			return true;
	return false;
}

bool CLsocketByUdp::getType(int &type)
{
	type = SOCK_DGRAM;
	return false;
}

bool CLsocketByUdp::getProto(protoent *& ppe)
{
	if((ppe = getprotobyname(transport.c_str())) == 0)
			return true;
	return false ;
}

bool CLsocketByUdp::startlisten(const int qlen)
{
		
	return false ;
}

int CLsocketByUdp::send(void * Buf,const int size)
{
	return 0;
}

int CLsocketByUdp::receive(void * Buf)
{
	return 0;
}
