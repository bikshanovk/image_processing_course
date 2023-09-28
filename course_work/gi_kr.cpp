#include <iostream>
//#include <conio.h>
#include <windows.h>
//#include <Wingdi.h>
#include <stdio.h>
using namespace std;

#pragma pack(1)

#define  MAXCOLORTC 	 //MAXCOLOR16 MAXCOLOR16 - 16 цветов
						 //MAXCOLOR256 - 256 цветов
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
} head_file, head_file_temp;

struct node
{
	unsigned char data:4;
} Pix;
//};

signed char str [768];

void Reverse(int *a, int *b)
{
   if (a < b)
   {
       *a += *b; *b = *a - *b; *a -= *b;
       Reverse(a + 1, b - 1);
   }
}

int color16(int nColor)
{
	int nTemp;
	switch(nColor) {
		case  0: nTemp = RGB(0  , 0  , 0  ); break; // черный
		case  1: nTemp = RGB(0  , 0  , 255); break; // синий
		case  2: nTemp = RGB(0  , 255, 0  ); break; // зеленый
		case  3: nTemp = RGB(0  , 255, 255); break; // голубой
		case  4: nTemp = RGB(255, 0  , 0  ); break; // красный
		case  5: nTemp = RGB(255, 0  , 255); break; // пурпурный
		case  6: nTemp = RGB(150, 75 , 0  ); break; // коричневый
		case  7: nTemp = RGB(187, 187, 187); break; // светло-серый
		case  8: nTemp = RGB(128, 128, 128); break; // серый
		case  9: nTemp = RGB(66 , 170  , 255); break; // светло-синий

		case 10: nTemp = RGB(144, 238, 144); break; // light green
		case 11: nTemp = RGB(224, 255, 255); break; // light cyan
		case 12: nTemp = RGB(255, 153, 153); break; // light red
		case 13: nTemp = RGB(255, 119, 255); break; // light magenta

		case 14: nTemp = RGB(255, 255, 0  ); break; // желтый
		case 15: nTemp = RGB(255, 255, 255); break; // белый
		default: nTemp = RGB(0  , 0  , 0  ); break;
	}
	return nTemp;
}

void main()
{
	FILE *F, *F2;
	int i, j, x, y;
	x=0; y = 767;
	//color_16
	//color_256;

//KR
int amount [256][2];
int delta  [256][256];
for (i = 0; i < 256; i++) {
	amount[i][0]=amount[i][1]=0;
	for (j = 0; j < 256; j++) {
          delta[i][j]=0;
	}
}
unsigned char palitra[256][4];
unsigned char pal16[16][4];

unsigned char temp;
while (true)
{


if(GetAsyncKeyState( VK_SHIFT))
{
		F = fopen("_Carib256.bmp", "rb");
		//F = fopen("CAT256.BMP", "rb");
		fread(&head_file,sizeof(head_file),1,F);


		fread(&palitra,sizeof(palitra),1,F);
//Print to the screen:
		for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				temp= getc(F);
				//putpixel(i, j, RGB (palitra [temp][2] ,palitra [temp][1], palitra [temp][0]));
				amount[temp][0]++; amount[temp][1]=(int)temp;
			}
		}

		wg->flush();
//END Print to the screen.
//resize(head_file.biwidth + 9 , head_file.biheight + 9);
fclose(F);


for (int k = 0; k < 5; k++) {
//Palitra processing:
//Select 16 most important colors:

//bool used[256]
for (i = 0; i < 16; i++)
{
	 int max = 50;
	 for (j = 0; j < 256; j++)
	 {
		if (amount[j][0]>amount[max][0])
		{
		   max=j;
		}
	 }
	 amount[max][0]=0;
	 pal16[i][2] = palitra [max][2];
	 pal16[i][1] = palitra [max][1];
	 pal16[i][0] = palitra [max][0];
}
}
//END Select 16 most important colors
int d16 [16];
for (i = 0; i < 256; i++)
{
	/*int delta = (pal16 [0][2]-palitra [0][2])*(pal16 [0][2]-palitra [0][2])+
				(pal16 [0][1]-palitra [0][1])*(pal16 [0][1]-palitra [0][1])+
				(pal16 [0][0]-palitra [0][0])*(pal16 [0][0]-palitra [0][0]); 	*/
	for (j=0; j < 16; j++)
	{
		d16[j] = (pal16 [j][2]-palitra [i][2])*(pal16 [j][2]-palitra [i][2])+
					 (pal16 [j][1]-palitra [i][1])*(pal16 [j][1]-palitra [i][1])+
					 (pal16 [j][0]-palitra [i][0])*(pal16 [j][0]-palitra [i][0]);
	}
	//Find closer color in 256 palette
	int min = 0;
	for (int k = 1; k < 16; k++)
	{
		if (d16[k]<d16[min]) {
		   min=k;
		}
	}

	//Change 256 color palette:
	palitra [i][2] = pal16 [min][2];
	palitra [i][1] = pal16 [min][1];
	palitra [i][0] = pal16 [min][0];
    palitra [i][3] = min; 			//Will be useful
}


F = fopen("_Carib256.bmp", "rb");
		//F = fopen("CAT256.BMP", "rb");
		fread(&head_file,sizeof(head_file),1,F);

		unsigned char palitra2[256][4];
		fread(&palitra2,sizeof(palitra2),1,F);
//Print to the screen:
		for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				unsigned char temp= getc(F);
				putpixel(i, j, RGB (palitra [temp][2] ,palitra [temp][1], palitra [temp][0]));
				amount[temp][0]++;
			}
		}

		wg->flush();
//END Print to the screen.
resize(head_file.biwidth + 9 , head_file.biheight + 9);
fclose(F);


putpixel(1,1,1);
}



//16 color file reading
if(GetAsyncKeyState(VK_ESCAPE))
{

F = fopen("_Carib256.bmp", "rb");
		//F = fopen("CAT256.BMP", "rb");
		fread(&head_file,sizeof(head_file),1,F);

		unsigned char palitra2[256][4];
		fread(&palitra2,sizeof(palitra2),1,F);
//Print to the screen:
		for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				unsigned char temp= getc(F);
				putpixel(i, j, RGB (palitra2 [temp][2] ,palitra2 [temp][1], palitra2 [temp][0]));
				amount[temp][0]++;
			}
		}

		wg->flush();
//END Print to the screen.
resize(head_file.biwidth + 9 , head_file.biheight + 9);
fclose(F);

}

if(GetAsyncKeyState(VK_CONTROL))
	{
		F = fopen("_Carib16.bmp", "rb");
		fread(&head_file,sizeof(head_file),1,F);
		fread(&color_16,sizeof(color_16),1,F);
		fclose(F);
		//change 16 color palette to my own:
		for (i = 0; i < 16; i++)
		{
			 color_16[i]=RGB(pal16[i][2], pal16[i][1], pal16[i][0]);
		}

    F = fopen("_Carib256.bmp", "rb");
	fread(&head_file_temp,sizeof(head_file_temp),1,F);
	unsigned char palitra2[256][4];
	fread(&palitra2,sizeof(palitra2),1,F);

	F2 = fopen("_Carib16_MY.bmp", "wb");
	fwrite(&head_file,sizeof(head_file),1,F2);
	fwrite(&color_16,sizeof(color_16),1,F2);



	//bypassing the image:
    for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++, i++)
			{
				//unsigned char temp= getc(F);
				//Read 2 pixels:
				unsigned char A = getc(F);
				unsigned char B = getc(F);
				unsigned char result = palitra[A][3]*16+palitra[B][3];
				fputc((int)result, F2);
				//putpixel(i, j, RGB (palitra [temp][2] ,palitra [temp][1], palitra [temp][0]));
				//amount[temp][0]++;
			}
		}
		fclose(F);
		fclose(F2);
		int temp = ftell(F);
		//Initialize:
		  j = head_file.biheight;
		  i = 0;
		while (!feof(F))
		{
			 unsigned char temp= getc(F);

			 putpixel(i, j, color_16[temp/16]);
			 //putpixel(i, j, RGB(0  , 255, 255));
			  i++;
			 putpixel(i, j, color_16[temp%16]);
			 //putpixel(i, j, RGB(0  , 255, 255));
			  i++;


			  if (i==head_file.biwidth) {
					i=0;
					j--;
			  }
		}

		temp = ftell(F);
		resize(head_file.biwidth + 9 , head_file.biheight + 9);
		wg->flush();
		fclose(F);

	}

//END KR
}
 }
