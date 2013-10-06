#include "PBusage.h"
#include <iostream>
using namespace std;

PBusage::PBusage()
{
	this->UsageExpression();
}

PBusage::~PBusage()
{

}

void PBusage::UsageExpression()
{
	cout<<"Usage:"<<endl;
	cout<<"\t\t-ld <path>	"<<endl;
	cout<<"\t\t-se			"<<endl;
	cout<<"\t\t-sa <path>	"<<endl;
	cout<<"\t\t-ad <name> <number>"<<endl;
	cout<<"\t\t-fd <path>	"<<endl;
	cout<<"\t\t-ls			"<<endl;
	cout<<"\t\t-qt			"<<endl;
}