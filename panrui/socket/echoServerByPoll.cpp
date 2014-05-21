#include "CLEventManagerByPoll.h"
#include "CLSocketPack.h"
#include <iostream>

using namespace std;

void * execallback(void * para);
void * listencallback(void * para)
{
	CLSocketPack * plisten = (CLSocketPack *)para;
	CLSocketPack * nConn = new CLSocketPack(plisten->Accept());

	CLEventManager * pcembp = CLEventManagerByPoll::GetInstance(10);
	pcembp->RegistObserver(nConn->getOriginal(),execallback,nConn,CALL_READ);
	
	return NULL;
}

void * execallback(void * para)
{
	CLSocketPack * pdeal = (CLSocketPack *)para;
	string recv;
	pdeal->Send(pdeal->Recv(recv));
	
	CLEventManager * pcembp = CLEventManagerByPoll::GetInstance(10);
	pcembp->RemoveObserver(pdeal->getOriginal());

	close(pdeal->getOriginal());
	delete pdeal;
	
	return NULL;
}



int main(int argc,char ** argv)
{
	if(argc != 2)
	{
		cout<<"wrong para"<<endl;
		exit(0);
	}

	CLEventManager * pcembp = CLEventManagerByPoll::GetInstance(10);
	CLSocketPack csp;

	string port = argv[1];
	csp.StartServer(port);

	pcembp->RegistObserver(csp.getOriginal(),listencallback,&csp,CALL_READ);
	
	timeval time;
	time.tv_usec = 0;
	time.tv_sec = 0;
	pcembp->StartMainLoop(time);

	return 0;
}
