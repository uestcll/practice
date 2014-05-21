#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int main()
{
	int fd1 = open("./file1",O_CREAT|O_WRONLY);
	int fd2 = open("./file1",O_CREAT|O_WRONLY);
	int fd3 = open("./file1",O_CREAT|O_WRONLY);

	int fd4 = open("./file2",O_CREAT|O_WRONLY);
	int fd5 = open("./file3",O_CREAT|O_WRONLY);

	cout<<fd1<<endl;
	cout<<fd2<<endl;
	cout<<fd3<<endl;
	cout<<fd4<<endl;
	cout<<fd5<<endl<<endl;
	getchar();
	close(fd4);

	int fd6 = open("./file4",O_CREAT|O_WRONLY);
	

	cout<<fd1<<endl;
	cout<<fd2<<endl;
	cout<<fd3<<endl;
	cout<<fd4<<endl;
	cout<<fd5<<endl;
	cout<<fd6<<endl;

	getchar();

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd6);
	close(fd5);

	return 0;
}
