#ifndef CLSOCKET_PACK_H
#define CLSOCKET_PACK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

class CLSocketPack
{
public:
	CLSocketPack(const CLSocketPack &);

	CLSocketPack(int socket);
	CLSocketPack();
	~CLSocketPack();

	bool Connect(string &port ,string &address);
	bool StartServer(string &port);
	
	CLSocketPack  Accept();
	int Send(string &toSend);
	string &Recv(string &toRecv);

	void setNonClean() const { m_isClean = false; }
	int  getOriginal(){ setNonClean(); return m_socket; }
private:

	CLSocketPack & operator = ( CLSocketPack &);
	
	int  m_socket;
	mutable	bool m_isClean;
};

#endif
