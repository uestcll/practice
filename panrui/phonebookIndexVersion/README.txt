不完全的测试。
Index 结构由26个分块组成

Index 

cur_p 		现在Index指向的是哪一个分块
IsIndirect[i] 	第i个分块是否是直接指向电话本的位移  true指向另一个index false指向电话本的位移
offset[i]	如果IsIndirect[i]为true,offset[i]存储另一个Index的地址，否则存储该块相对于电话本的位移