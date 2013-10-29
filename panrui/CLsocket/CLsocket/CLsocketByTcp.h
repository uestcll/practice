#ifndef _CL_SOCKET_BY_TCP_
#define _CL_SOCKET_BY_TCP_

#include "CLsocket.h"

class CLsocketByTcp:public CLsocket
{
private:
	bool isInit;

protected:
	virtual bool getPort(unsigned short &net_port,const string &port);
	virtual bool getType(int &type);
	virtual bool getProto(protoent *&ppe);
	virtual bool startlisten(const int qlen);

public:
	CLsocketByTcp();
	CLsocketByTcp(int fd);
	virtual ~CLsocketByTcp();

	virtual int send(void * Buf,const int size);
	virtual int receive(void * Buf);


};
#endif
