#include "Huffman.h"
#include "Decode.h"
#include "Encode.h"

#include <string.h>
void main()
{
	hTree * pp = initHTreeMap();
	hTree * ss = loadFile(pp,"D:\\PanRui\\20100916.mp4");

	char leftBit = EncodeToNewFile("D:\\PanRui\\20100916.mp4","D:\\PR.bin",pp);
	DecodeFromFile("D:\\PR.bin","D:\\PR.mp4",ss,leftBit);

	destoryHTreeMap(pp,ss);
	

}