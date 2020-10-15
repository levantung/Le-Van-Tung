static int labelmaker_handler(*r)
{
	void *iptr;
	int sz = 0;
	if(strcmp(r->handler,"labelmaker"))
	{
		return DECLINED;
	}
		r->content_type="content-type:image/gif";
	if(!r->headler_only)
	{
		int text=0,background=0,x=0,y=0,size=30,string_rectangle[8];
		double angle=0.0;
		char value[255]="hello";
		char font[256]="/usr/share/fonts/truetype/DejaVuSans.ttf";
		char *err=NULL;
		gdImagePtr im_out=NULL;
		decode_value(r,"TEXT=",(char *)&value,255);
		err=gdImageStringFT(NULL,&string_rectangle[0],0,font,size,angle,0,0,value);
		x=string_rectangle[2]-string_rectangle[6]+6;
		y=string_rectangle[3]-string_rectangle[7]+6;
		im_out=gdImageCreate(x,y);
		background=gdImageColorAllocate(im_out,0,0,0);
		text=gdImageColorAllocate(im_out,255,0,255);
		x=3-string_rectangle[6];
		y=3-string_rectangle[7];
		err=gdImageStringFT(im_out,&string_rectangle[0],text,font,size,angle,x,y,value);
		iptr=gdImageGifPtr(im_out,&sz);
		ap_rwrite(iptr,sz,r);
		gdFree(iptr);
		gdImageDestroy(im_out);

	}
	return ok;
}