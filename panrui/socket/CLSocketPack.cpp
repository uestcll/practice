#include "CLSocketPack.h"
#include <errno.h>
#include <iostream>
using namespace std;

CLSocketPack::CLSocketPack():m_socket(-1),m_isClean(false)
{

}

CLSocketPack::CLSocketPack(int socket):m_socket(socket),m_isClean(true)
{

}

CLSocketPack::CLSocketPack(const CLSocketPack & oldSocket):m_socket(oldSocket.m_socket),m_isClean(true)
{
	oldSocket.setNonClean();
}

CLSocketPack::~CLSocketPack()
{
	if(m_isClean )
	{
		close(m_socket);
		m_socket = -1;
	}
}

CLSocketPack CLSocketPack::Accept()
{
	CLSocketPack Conn;
	Conn.m_socket = ::accept(m_socket ,NULL ,NULL);
	return Conn;
}

bool CLSocketPack::Connect(string &port,string &address)
{
	sockaddr_in addr;
	bzero(&addr ,sizeof(sockaddr_in ));
	
	if(m_socket == -1)
	{
		m_socket = socket(AF_INET,SOCK_STREAM,0);
		m_isClean = true;
	}
	
	addr.sin_family = AF_INET;

	struct servent * sp = NULL;
	if(NULL == (sp = getservbyname(port.c_str(),"tcp")))
	{
		addr.sin_port = htons((unsigned short )atoi(port.c_str() ) );		
	}
	else
	{
		addr.sin_port = sp->s_port;
	}

	struct hostent * hp = NULL;
	if(NULL == (hp = gethostbyname(address.c_str())))
	{
		inet_pton(AF_INET ,address.c_str() ,&addr.sin_addr);
	}
	else
	{
		addr.sin_addr = **((struct in_addr **)hp->h_addr_list );
	}

	int retCode = connect(m_socket ,(sockaddr *)&addr ,sizeof(sockaddr_in ) );
	if(retCode != 0)
	{
		cout<<"error happened in connect()"<<endl;
		close(m_socket);
		m_socket = -1;
	}

	return retCode;
}

bool CLSocketPack::StartServer(string &port)
{

	if(m_socket == -1)
	{
		m_socket = socket(AF_INET ,SOCK_STREAM ,0);
		m_isClean =true;
	}
	else
	{
		return false;
	}
	
	sockaddr_in addr;
	bzero(&addr ,sizeof(sockaddr_in ));

	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;

	struct servent * sp = NULL;
	if(NULL == (sp = getservbyname(port.c_str(),"tcp")))
	{
		addr.sin_port = htons((unsigned short )atoi(port.c_str()));		
	}
	else
	{
		addr.sin_port = sp->s_port;
	}
	if(-1 == bind(m_socket ,(sockaddr *)&addr ,sizeof(sockaddr_in )))
	{
		cout <<"error happened in bind()"<<errno<<endl;
		close(m_socket);
		m_socket = -1;
		return false;
	}

	if(-1 == listen(m_socket , SOMAXCONN) )
	{
		cout <<"error happened in listen()"<<errno<<endl;
		close(m_socket);
		m_socket = -1;
		return false;
	}

	return true;
}

int CLSocketPack::Send(string &toSend)
{
	toSend.insert(toSend.begin() ,sizeof(int ) ,0);
	* (int *)&toSend[0] = toSend.size();
	
	return send(m_socket ,toSend.c_str(),toSend.size() ,0 );
}

string & CLSocketPack::Recv(string &toRecv)
{
#define BUF_SIZE 1024
	
	if(toRecv.size())
	{
		toRecv.clear();
	}
	
	char buf[BUF_SIZE] = {0};
	int leftSize = 4;
	bool is_FirstRecv = true;
	int r_size = 0;

	while((r_size = recv(m_socket ,buf ,BUF_SIZE>leftSize?leftSize:BUF_SIZE ,0 )))
	{
		if(r_size == -1)
		{
			return toRecv;
		}

		if(is_FirstRecv)
		{
			is_FirstRecv =false;
			leftSize = *(int *)&buf;
		}
		else
		{
			toRecv.append(buf ,r_size );	
		}

		leftSize -= r_size;
		if(leftSize<=0)
		{
			return toRecv;
		}
	}

	return toRecv;
}












