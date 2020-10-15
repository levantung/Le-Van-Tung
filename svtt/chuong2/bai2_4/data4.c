/********************
C Programming in linux (c) David Haskins 2008
data4.c
********************/
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	char *token=NULL;
	char colour1[256]="";
	char colour2[256]="";
	int wide = 0;
	int high = 0;
	int columns = 0;
	int rows = 0;
	token=(argv[1]);
	strcpy(colour1,token);
	token=(argv[2]);
	strcpy(colour2,token);
	token=(argv[3]);
	wide=atoi(token);
	token=(argv[4]);
	high=atoi(token);
	printf("content-type:text/html\n\n");
	printf("<html>\n");
	printf("<body bgcolor=\"%s\">\n",colour1 );
	printf("<center>\n");
	printf("<table bgcolor=\"%s\"border=2>\n",colour2 );
	for(rows=1;rows<=high;rows++)
	{
		printf("<tr>\n");
		for(columns=1;columns<=wide;columns++)
		{
			printf("<td><h6>row=%dcell=%d</h6></td>\n",rows,columns);
		}
		printf("</tr>\n");
	}
	printf("</table>\n");
	printf("</body>\n");
	printf("</html>\n");
	return 0;
}