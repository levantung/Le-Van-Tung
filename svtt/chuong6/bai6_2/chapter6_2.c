/***************************
C Programming in linux (c) David Haskins 2008
chapter4_2.c
********************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gd.h>
#include<gdfonts.h>
#include"c_in_linux.h"
int main(int argc,char *argv[],char *env[])
{
	int text=0,background=0,height=50,width=0,x=0,y=0,size=30,string_rectangle[8];
	double angle=0.0;
	char value[255]="";
	//OpenSuse TrueType Font
	char font[256]="/usr/share/fonts/truetype/DejaVuSans.ttf";
	//Ubuntu truetype font
	char font[256]="/usr/share/fonts/truetype/ttf-Dejavu/DejaVuSans.ttf";
	char *err =NULL;
	glImagePtr im_out=NULL;
	decode_value("TEXT=",(char *)&value,255);
	//call gdImageStringFT with NULL image to obtain size
	err=gdImageStringFT(NULL,&string_retangle[0],0,font,size,angle,0,0,value);
	x=string_retangle[2]-string_retangle[6]+6;
	y=string_retangle[3]-string_retangle[7]+6;
	//create an image big enough for the string plus a little space
	im_out=gdImageCreate(x,y);
	//allocate colours
	background=gdImageColorAllocate(im_out,0,0,0);
	text=gdImageColorAllocate(im_out,255,0,255);
	//get starting position
	x=3-string_rectangle[6];
	y=3-string_rectangle[7];
	//draw the string 
	err=gdImageStringFT(im_out,&string_retangle[0],text,font,size,x,y,value);
	//output
	printf("content-type:image/gif\n\n");
	gdImageGif(im_out,stdout);
	gdImageDestroy(im_out);
	return 0;

}