int main(int argc,char *argv[])
{
	FILE *out =NULL;
	MYSQL *conn=NULL;
	MYSQL_RES*result= NULL;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	char SQL[STRINGSIZE]="";
	char BIT[STRINGSIZE]="";
	char SQLUPDATE[STRINGSIZE]="";
	char SQLDELETE[STRINGSIZE]="";
	int rc=0,i=0,num_fields=0;
	//CREATE DIRECTORY/////////
	sprintf(BIT,"mkdir~/public_html/%s",argv[1]);
	system(BIT);
	//BUILD CSS///////
	sprintf(BIT,"../%s/%s.css",argv[1],argv[1]);
	out=fopen(BIT,"w");
	fprintf(out, "table{width:800;vertical-align:top;}\n" );
	fprintf(out, "th{font-size:80%; color:#fd9208; vertical-align:bottom;text-align:left;}\n" );
	fprintf(out, "th{font-size:80%; color:#fd9208; vertical-align:bottom;text-align:left;}\n" );
	fprintf(out, "input{font-size:80%; color:#1918\n",196419;}\n);
	fprintf(out ,*a,{font-size:65%;color:#000000;}\n");
		fclose(out);
		)