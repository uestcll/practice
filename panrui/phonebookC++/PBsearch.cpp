#include "PBsearch.h"

PBsearch::PBsearch()
{

}

PBsearch::~PBsearch()
{

}

bool PBsearch::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-fd")
		return true;
	return false;
}

bool PBsearch::executeCMD(vector<PBitem *> &pb_item,string para)
{
	vector<PBitem *>::iterator	it = pb_item.begin();
	string info;

	if(!analysisPara(para,info))
	{
		cout<<"para wrong while searching"<<endl;
		return true;
	}

	while(it != pb_item.end())
	{
		if((*it)->getName().find(info,0)!=string::npos)
		{
			cout<<(*it)->getName()<<'\t'<<(*it)->getNum()<<endl;
		}
		else if((*it)->getNum().find(info,0)!=string::npos)
		{
			cout<<(*it)->getName()<<'\t'<<(*it)->getNum()<<endl;
		}
		else ;

		it++;
	}

	return true;
}

bool PBsearch::analysisPara(string para,string &info)
{
	string::size_type info_f = para.find_first_not_of(' ',0);
	if(info_f == string::npos)
		return false;

	info = para.substr(info_f,para.length()-info_f);

	return true;	
}