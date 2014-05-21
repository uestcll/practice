#include "CLEventManagerBySelect.h"
#include <iostream>
#include <string>

using namespace std;

void * connCallBack(void *);

void * listenCallBack(void * para)
{
	CLSocketPack * pListen = (CLSocketPack *)para;
	CLSocketPack * Conn = new CLSocketPack(pListen->Accept());

	    
	CLEventManager * pM = CLEventManagerBySelect::GetInstantce();     
	pM->RegistObserver(Conn->getOriginal(),connCallBack,Conn,CALL_READ);
	
	return NULL;
}

void * connCallBack(void * para)
{
	CLSocketPack * pconn = (CLSocketPack *)para;

	string toRecv;

	pconn->Send(pconn->Recv(toRecv));
	
	CLEventManager * pM = CLEventManagerBySelect::GetInstantce();
	pM->RemoveObserver(pconn->getOriginal());

	close(pconn->getOriginal());
	delete pconn;

	return NULL;
}




int main(int argc ,char ** argv)
{
	if(argc != 2)
	{
		cout<<"error on para"<<endl;
		return -1;
	}

	CLSocketPack listensock;


	string port = argv[1];
	listensock.StartServer(port);

	CLEventManager * pM = CLEventManagerBySelect::GetInstantce();

	pM->RegistObserver(listensock.getOriginal(),listenCallBack,&listensock,CALL_READ);

	timeval wait;
	bzero(&wait,sizeof(timeval));

	pM->StartMainLoop(wait);

	return 0;
}
