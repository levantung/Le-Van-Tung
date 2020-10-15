/***************************
C Programming in linux (c) David Haskins 2008
chapter4_2.c
********************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gdfonts.h>
#include<gd.h>
#include<c_in_linux.h>

int main(int argc,char *argv[],char *env[])
{
	int text=0,background=0,height=50,width=0;
	char value[255]="";
	gdImagePtr im_out=NULL;
	decode_value("TEXT=",(char *)&value,255);
	width=(strlen(value)*10)+5;
	im_out=gdImageCreate(width,height);
	background=gdImageColorAllocate(im_out,255,0,255);
	text=gdImageColorAllocate(im_out,0,0,255);
	gdImageFilledRectangle(im_out,0,0,width-1,height-1,background);
	gdImageString(im_out,gdFontGetSmall(),10,5,(unsigned char *),value,text);
	printf("content-type:image/gif\n\n");
	gdImageGif(im_out,stdout);
	gdImageDestroy(im_out);
	return 0;
}