#ifndef _CL_SOCKET_BY_UDP_
#define _CL_SOCKET_BY_UDP_

#include "CLsocket.h"

class CLsocketByUdp:public CLsocket
{
private:
	bool isInit;

protected:
	virtual bool getPort(unsigned short &net_port,const string &port);
	virtual bool getType(int &type);
	virtual bool getProto(protoent *& ppe);
	virtual bool startlisten(const int qlen);

public:

	CLsocketByUdp();
	CLsocketByUdp(int fd);
	virtual ~CLsocketByUdp();



	virtual int send(void * Buf,const int size);
	virtual int receive(void * Buf);


};
#endif
