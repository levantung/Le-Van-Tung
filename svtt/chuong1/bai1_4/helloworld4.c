/*******************
C Programming in linux(c) Davidc Haskins 2008
helloworld4.c
*******************/
#include<stdio.h>
int main(int argc ,char *argv[],char *env[])
{
	int i=0;
	printf("content-type:text/plain\n\n");
	printf("hello,you are still learning C!!\n");
	printf("number of arguments to the main function:%d\n",argc );
	for (int i = 0; i < argc; ++i)
	{
		printf("argument number %d is %s\n",i,argv[i]);
	}
	i=0;
	printf("enviroment variables:\n");
	while(env[i])
	{
		printf("env[%d]=%s\n",i,env[i]);
		i++;
	}
	return 0;
}