#ifndef _CL_SOCKET_
#define _CL_SOCKET_

#include <string>
#include <netdb.h>
using namespace std;
class CLsocket
{
private:
protected:
	int fd;
	sockaddr_in sin;
	bool isServer;

	virtual bool getPort(unsigned short &net_port,const string & port) = 0;
	virtual bool getType(int &type) = 0;
	virtual bool getProto(protoent *& ppe) = 0;
	virtual bool startlisten(const int qlen) = 0;
	void getSocket(const string & host,const string &port);
public:
	explicit CLsocket();
	virtual ~CLsocket();

	int connectsocket(const string & host,const string &port);
	int passivesocket(const string &port,const int qlen);
	virtual int send(void * Buf,const int size) = 0;
	virtual int receive(void * Buf) = 0;

};

#endif
