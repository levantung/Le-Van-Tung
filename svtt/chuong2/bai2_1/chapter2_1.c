/*******************************
C Programming in linux (c) David Haskins
chapter2_1.c
********************************/
#include<stdio.h>
#define stringsize 256
int main(int argc,char *argv[])
{	
	char town[stringsize]="guidford";
	char county[stringsize]="surrey";
	char country[stringsize]="great britain";
	int population = 66773;
	float latitude =51.238599;
	float longitude = -0.566257;
	printf("town name:%s population:%d\n",town,population );
	printf("county:%s\n",county);
	printf("country:%s\n",country);
	printf("location latitude: %f longitude:%f\n",latitude,longitude);
	printf("char=%d byte int =%d bytes float =%d bytes\n",sizeof(char),sizeof(int),sizeof(float) );
	printf("memory used:%d bytes\n",((stringsize*3)*sizeof(char)) +sizeof(int)+(2*sizeof(float)));	
	return 0;
}