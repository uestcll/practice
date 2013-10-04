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
	analysisPara(para,name,num);
	pb_item.push_back(new PBitem(name,num));
	return true;
}

void PBaddNew::analysisPara(string para,string &name,string &num)
{
	string::size_type name_f = para.find_first_not_of(' ',0);
	string::size_type name_l = para.find_first_of(' ',name_f);
	
	string::size_type num_f = para.find_first_not_of(' ',name_l);

	name = para.substr(name_f,name_l - name_f);
	num = para.substr(num_f,para.length()-num_f);
}