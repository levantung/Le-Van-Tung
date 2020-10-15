
/********************I
C Programming in linux(c) David Haskins 2008
chapter4_1.c
****************/
#include<stdio.h>
#include<string.h>
int main(int argc,char *env[])
{
	printf("content-type:text/html\n\n<html><body=#23abe2>\n");
	char value[256];
	strncpy(value,"QUERY_STRING", 255);
	printf("QUERY_STRING:%s<BR>\n",value);
	printf("<form>\n");
	printf("<input type=\"TEXT\"name=\"ITEM1\">\n");
	printf("<input type=\"TEXT\"name=\"ITEM2\">\n");
	printf("<input type=\"SUBMIT\">");
	printf("</form></body></html>\n");
	return 0;
}