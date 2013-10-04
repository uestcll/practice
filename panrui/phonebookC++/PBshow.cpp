#include "PBshow.h"

PBshow::PBshow()
{

}

PBshow::~PBshow()
{

}

bool PBshow::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-ls")
		return true;
	return false;	

}

bool PBshow::executeCMD(vector<PBitem *> &pb_item,string para)
{
	vector<PBitem *>::iterator it = pb_item.begin();
	
	while(it!=pb_item.end())
	{
		cout<<(*it)->getName()<<"\t"<<(*it)->getNum()<<endl;
		it++;
	}
	return true;
}