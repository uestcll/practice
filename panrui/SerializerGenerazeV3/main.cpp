#include "CLSerializerAndDeserializerCreater.h"

int main()
{
	CLSerializerAndDeserializerCreater tmp("D:\\test");

	tmp.initEnvironment();
	tmp.creatSerializerAndDeserializer();
	tmp.destroyEnvironment();

	return 0;
}