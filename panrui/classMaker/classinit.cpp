#include <iostream>
#include "PBmainLoop.h"
using namespace std;


int main(int argc,char * argv[])
{
	if(argc == 3)
	{
		if(argv[2][0] == 'y')
		PBtool::init(argv[1],true);
		else PBtool::init(argv[1],false);
	}
	else if(argc == 2)
	{
		PBtool::init(argv[1],false);
	}
	else
	{
		string className;
		char   isNon;
		cout<<"className:";
		cin>>className;
		cout<<"if wanna have a private copy constructer? y/n ";
		cin>>isNon;
		if(isNon == 'y')
			PBtool::init(className,false);
		else PBtool::init(className,true);
	}
	PBmainLoop * mainloop = new PBmainLoop;
	mainloop->mainloop();
	delete mainloop;

}


