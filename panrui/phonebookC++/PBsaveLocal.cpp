#include "PBsaveLocal.h"

PBsaveLocal::PBsaveLocal()
{
	pb_save = new PBsave();
}

PBsaveLocal::~PBsaveLocal()
{
	delete pb_save;
}

bool PBsaveLocal::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-se")
		return true;
	return false;
}

bool PBsaveLocal::executeCMD(vector<PBitem *> &pb_item,string para)
{
	pb_save->doSave(DEFAULT_PATH,pb_item);
	return true;
}