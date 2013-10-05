#include "PBload.h"

PBload::PBload()
{
	pb_addNew = new PBaddNew();
}

PBload::~PBload()
{
	delete pb_addNew;
}

bool PBload::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-ld")
		return true;
	return false;
}

bool PBload::executeCMD(vector<PBitem *> &pb_item,string para)
{
	string path;

	if(!analysisPara(para,path))
	{
		cout<<"error while adding new item"<<endl;
		return true;
	}

	istr = new ifstream();
	istr->open(path,ios::binary);

	if(!istr->is_open())
	{
		cout<<"open file fail while loading file"<<endl;
		return true;
	}

	string additem;
	while(istr->peek()!=EOF)
	{
		getline(*istr,additem,'\n');
		pb_addNew->executeCMD(pb_item,additem);
	}

	istr->close();
	return true;
}

bool PBload::analysisPara(string para,string &path)
{
	string::size_type path_f = para.find_first_not_of(' ',0);
	if(path_f == string::npos)
		return false;

	path = para.substr(path_f,para.length()-path_f);
	
	return true;
}

