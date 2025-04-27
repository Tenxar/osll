#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
	int fd,fd1;
	char * myfifo = "myfifo";
	char * myfifo1 = "myfifo1";
	char buff[1024];
	
	mkfifo(myfifo,0666);
	mkfifo(myfifo1,0777);

	fd=open(myfifo,O_WRONLY);

	write(fd,"Welcome... \n to PES MCOE \nPune. \nMaharashtra \nIndia.",sizeof("Welcome... \n to PES MCOE \nPune. \nMaharashtra \nIndia."));

	close(fd);

	unlink(myfifo);

	fd1=open(myfifo1,O_RDONLY);
	read(fd1,buff,sizeof(buff));
	printf("%s", buff);
	unlink(myfifo1);
	close(fd1);
	return 0;
}
