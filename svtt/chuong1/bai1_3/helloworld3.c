/*******************************
*C Programming in linux (c) David Haskins
*helloworld3.c
*******************************/
#include<stdio.h>
int main(int n,char *a[])
{
	int i=0;
	printf("content-type:text/plain\n\n");
	printf("hello,you are still learning C!!\n");
	printf("Number of arguments to the main function:%d\n",n);
	for(i=0;i<n;i++)
	{
		printf("argument number %d is %s\n",i,a[i]);
	}
	return 0;
}