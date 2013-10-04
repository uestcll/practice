#include "PBquit.h"
PBquit::PBquit()
{

}

PBquit::~PBquit()
{

}

bool PBquit::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-qt")
		return true;
	return false;	
}

bool PBquit::executeCMD(vector<PBitem *> &pb_item,string para)
{
	return false;
}
