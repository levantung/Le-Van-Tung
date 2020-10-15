/****************************
C Programming in linux(c) David Haskins
helloworld2.c
****************************/
#include<stdio.h>
int main(int argc,char *argv[])
{
	int i=0;
	printf("hello,you are learning C!!\n");
	printf("Number of arguments to the main function:%d\n",argc);
	for(i=0;i<argc;i++)
	{
		printf("argument number:%d is %s\n",i,argv[i]);

	}
	return 0;
}