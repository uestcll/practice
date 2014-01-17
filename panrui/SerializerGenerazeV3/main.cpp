#include "CLSerializerAndDeserializerCreater.h"

int main()
{
	CLSerializerAndDeserializerCreater tmp(".");

	tmp.initEnvironment();
	tmp.creatSerializerAndDeserializer();
	tmp.destroyEnvironment();

	return 0;
}