/***************************
C Programming in linux (c) David Haskins 2008
chapter4_2.c
********************/
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
#include"c_in_linux.h"
int main(int argc,char *argv[],char *env[])
{
	char value1[255]="",value2[255]="",SQL[1024]="";
	int rc = 0 ;
	MYSQL *conn = NULL;
	MYSQL_RES *result= NULL;
	MYSQL_ROW row;
	printf("content-type:text/html\n\n<html><body bgcolor=#23abe2>\n");
	strncpy(value1,"QUERY_STRING",255);
	printf("QUERY_STRING:%s<BR>\n",value1);
	printf("<form>\n");
	//call the decode_value function to get value of "ITEM1"
	decode_value("ITEM1=",(char *)&value1,255);
	if(strlen(value1)>0)
	{
		printf("<input type=\"TEXT\" name =\"ITEM1\"value=\"%s\">\n",value1 );

	}
	else
	{
		printf("<input type=\"TEXT\" name =\"ITEM1\">\n");
	}
	//call the decode_value function to get value of "ITEM2"
	decode_value("ITEM2=",(char *)&value2,255);
	if(strlen(value2)>0)
	{
		printf("<input type=\"TEXT\" name =\"ITEM2\"value=\"%s\">\n",value2 );

	}
	else
	{
		printf("<input type=\"TEXT\" name =\"ITEM2\">\n");
	}
	printf("<input type =\"SUBMIT\">");
	printf("</form></body></html>\n");
	//OPEN DATABASE
	conn=mysql_init((MYSQL *)0);
	mysql_option(conn,MYSQL_READ_DEFAULT_GROUP,"mysqlcapi");
	mysql_real_connect(conn,"localhost","","","test",0,NULL,0);
	//INSERT IF THERE IS ANY DATA
	if(strlen(value1)>0|| strlen(value2)>0)
	{
		sprintf(SQL,"insert into CIL values('%s','%s')",value1,value2);
			rc=mysql_query(conn,SQL);
	}
	//READ
	rc=mysql_query(conn,"select *from CIL");
	result=mysql_use_result(conn);
	while((row=mysql_fetch_row(result))!=NULL)
	{
		printf("item1=%s  item2=%s<br>",row[0],row[1] );
	}
	mysql_free_result(result);
	mysql_close(conn);
	return 0;
}