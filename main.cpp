#include "phonebook.h"

int main()
{
	phoneNum * p_numHead = (phoneNum *)malloc(sizeof(phoneNum));
	Tools * tool = (Tools *)malloc(sizeof(Tools));

	initHead(p_numHead,tool);
	mainLoop(tool);
}
