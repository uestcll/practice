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
	if(!analysisPara(para,name,num))
	{
		cout<<"wrong para while adding item"<<endl;
		PBusage usage;
		return true;
	}

	pb_item.push_back(new PBitem(name,num));
	return true;
}

bool PBaddNew::analysisPara(string para,string &name,string &num)
{
	string::size_type name_f = para.find_first_not_of(' ',0);
	if(name_f == string::npos)
		return false ;

	string::size_type name_l = para.find_first_of(' ',name_f);
	if(name_l == string::npos)
		return false;

	string::size_type num_f = para.find_first_not_of(' ',name_l);
	if(num_f == string::npos)
		return false;


	name = para.substr(name_f,name_l - name_f);
	num = para.substr(num_f,para.length()-num_f);
	return true;
}