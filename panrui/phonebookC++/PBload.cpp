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

	if(!PBTool::analysisPara(para,path))
	{
		cout<<"error while adding new item"<<endl;
		return true;
	}

	istr = new ifstream();
	istr->open(path.c_str(),ios::binary);

	if(!istr->is_open())
	{
		cout<<"open file fail while loading file"<<endl;
		PBusage usage;
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


