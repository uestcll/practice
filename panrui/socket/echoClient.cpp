#include "CLSocketPack.h"
#include <iostream>

using namespace std;

int main(int argc,char **argv)
{
	if(argc != 4)
	{
		cout<<"para error"<<endl;
	}

	CLSocketPack sp;
	string port = argv[1];
	string host = argv[2];
	string msg = argv[3];
	sp.Connect(port,host);

	sp.Send(msg);

	string msg2;
	sp.Recv(msg2);

	cout<<msg2<<endl;

	return 0;
}
