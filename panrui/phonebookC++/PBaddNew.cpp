#include "PBaddNew.h"

PBaddNew::PBaddNew()
{

}

PBaddNew::~PBaddNew()
{

}

bool PBaddNew::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-ad")
		return true;
	return false;
}

bool PBaddNew::executeCMD(vector<PBitem *> &pb_item,string para)
{
	string name;
	string num;
	if(!PBTool::analysisPara(para,name,num))
	{
		cout<<"wrong para while adding item"<<endl;
		PBusage usage;
		return true;
	}

	pb_item.push_back(new PBitem(name,num));
	return true;
}

