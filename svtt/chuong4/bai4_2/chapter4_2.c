/***************************
C Programming in linux (c) David Haskins 2008
chapter4_2.c
********************/
#include<stdio.h>
#include<string.h>
void decode_value(const char *key,char *value,int size)
{
	int length=0,i=0,j=0;
	char *pos1='\0',*pos2='\0';
	//if the string is in the query string
	if((pos1= strstr(("QUERY_STRING"),key))!=NULL)
	{
		//find start of value for this key
		for(i=0;i<strlen(key);i++)pos1++;
		//find length of the value
		if((pos2=strstr(pos1,"&"))!=NULL)
		{
			length=pos2-pos1;
		}
		else
		{
			length=strlen(pos1);

		}
		for(i=0,j=0;i<length;i++,j++)
		
		if(j<size)
		{
			value[j]=pos1[i];
		}
		//add NULL character to end of the value
		if(j<size)
		{
			value[j]='\0';
		}
		else
		{
			value[size-1]='\0';
		}
		
	}
}
int main(int argc,char *argv[],char *env[])
{
	printf("content-type:text/html\n\n<html><body bgcolor = #23abe2>\n" );
	char value[255]="";
	strncpy(value,"QUERY_STRING",255);
	printf("QUERY_STRING:%s<BR>\n",value );
	printf("<form>\n");
	//call the decode_value function to get value  "ITEM1"
	decode_value("ITEM1=",(char *) &value,255);
	if(strlen(value)>0)
	{
		printf("<input type=\"TEXT\" name=\"ITEM1\" value=\"%s\">\n",value);
	}
	else
	{
		printf("<input type=\"TEXT\" name=\"ITEM1\">\n");
	}
	//call the decode_value function to get value of "ITEM2"
	decode_value("ITEM2=",(char *) &value,255);
	if(strlen(value)>0)
	{
		printf("<input type=\"TEXT\" name=\"ITEM2\" value=\"%s\">\n",value);
	}
	else
	{
		printf("<input type=\"TEXT\" name=\"ITEM2\">\n");
	}
	printf("input type=\"SUBMIT\">");
	printf("</form></body></html>\n");
	return 0;
}