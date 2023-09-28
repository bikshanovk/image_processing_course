#include <iostream>
//#include <conio.h>
#include <windows.h>
//#include <Wingdi.h>
#include <stdio.h>
using namespace std;

#pragma pack(1)

#define  MAXCOLORTC  	 //MAXCOLORTC 	// MAXCOLOR16 - 16 цветов
						 //MAXCOLOR256 //- 256 цветов
						 //MAXCOLORTC - 16м цветов True Color
#include "wingraph.h"

struct  head {
        short bftype;
        long  bfsize;
		short rez1, rez2;
        long  bfoffbits;
        long  bisize;
        long  biwidth;
        long  biheight;
        short biplanes;
		short bibitcount;
        long  bicompression;
		long  bisizeimage;
		long  bix;
        long  biy;
        long  biclrused;
		long  biclrimp;
} head_file;

signed char str [768];

void main()
{

FILE *F, *F2;
F = fopen("_Carib256.bmp", "rb");
//F = fopen("CAT256.BMP", "rb");
fread(&head_file,sizeof(head_file),1,F);
resize(head_file.biwidth + 9 , head_file.biheight + 9);
unsigned char palitra[256][4];
fread(&palitra,sizeof(palitra),1,F);
int i, j, x, y;
x=0; y = 767;
x=ftell(F);
//Lab2
/*
//Palette conversion:
for (i = 0; i < 256; i++)
{
	palitra[i][0]=palitra[i][1]=palitra[i][2]=
	(palitra[i][0]+palitra[i][1] +palitra[i][2] )/3;
}
//END Palette conversion:
*/
/*
//Print to the screen:
for (j = head_file.biheight-1; j >= 0; j--)
{
   for (i = 0; i < head_file.biwidth; i++)
	{
		unsigned char temp= getc(F);
		if (j>(head_file.biheight-16)) {
			temp = random(255);
			putpixel(i, j, RGB (random(255), random(255), random(255)));
		} else if (j<15)
		{
			putpixel(i, j, RGB (random(255), random(255), random(255)));
		} else if ((i<15)||(i>head_file.biwidth-16))
		{
			putpixel(i, j, RGB (random(255), random(255), random(255)));
		} else
		{
			putpixel(i, j, RGB (palitra [temp][2] ,palitra [temp][1], palitra [temp][0]));
		}
	}

}
//END Print to the screen.
*/

//New file:
F2 = fopen("_CaribFR.bmp", "wb");
fwrite(&head_file,sizeof(head_file),1,F2);
fwrite(&palitra,sizeof(palitra),1,F2);

for (j = head_file.biheight-1; j >= 0; j--)
{
   for (i = 0; i < head_file.biwidth; i++)
	{
		unsigned char temp= getc(F);
		if (j>(head_file.biheight-15) || j<15) {
			fputc(random(255),F2);
		}
		else if ((i<15)||(i>head_file.biwidth-16))
		{
			fputc(random(255),F2);
		} else
		{
			fputc(temp,F2);
		}
	}
}
for (j = head_file.biheight-1; j >= 0; j--)
{
   //fread(&stringB,sizeof(stringB),1,F);
   for (i = 0; i < head_file.biwidth; i++)
	{
		unsigned char temp= getc(F);
		fputc(temp,F2);
	}
}
fclose(F2);
//END New File Cration

fclose(F);
}
//END lab2
