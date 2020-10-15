/*****************************
C Programming in linux (c) David Haskins 2008
func1.c
*****************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
double doit(int number1,int number2)
{	double result = 0;
 return result = sqrt((double)(number1+number2));


}
int main(int argc,char *argv[])
{		
	int n1=0,n2=0,i=0;
	double result = 0;
	n1= atoi(argv[1]);
	n2= atoi(argv[2]);
	printf("content-type:text/html\n\n<html><body>\n");
	for(i=1;i<100;i++)
	{
		result=doit(n1+i,n2*i);
		printf("%f",result );
	}
	printf("</body></html>\n");
	return 0;
}