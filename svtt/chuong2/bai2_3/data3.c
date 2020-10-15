/********************************
CProgramming in linux (c) David Haskins 2008
data3.c
********************************/
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[],char *env[])
{	
	printf("content-type:text/html\n\n");
	printf("<html>\n");
	printf("<body bgcolor=\"%s\">\n",argv[1] );
	printf("<body>\n");
	printf("<html>\n");
	return 0;
}



