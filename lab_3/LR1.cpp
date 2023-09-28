#include <iostream>
//#include <conio.h>
#include <windows.h>
//#include <Wingdi.h>
#include <stdio.h>
using namespace std;

#pragma pack(1)

#define  MAXCOLORTC 	 //MAXCOLOR16 MAXCOLOR16 - 16 ������
						 //MAXCOLOR256 - 256 ������
						 //MAXCOLORTC - 16� ������ True Color
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
		case  0: nTemp = RGB(0  , 0  , 0  ); break; // ������
		case  1: nTemp = RGB(0  , 0  , 255); break; // �����
		case  2: nTemp = RGB(0  , 255, 0  ); break; // �������
		case  3: nTemp = RGB(0  , 255, 255); break; // �������
		case  4: nTemp = RGB(255, 0  , 0  ); break; // �������
		case  5: nTemp = RGB(255, 0  , 255); break; // ���������
		case  6: nTemp = RGB(150, 75 , 0  ); break; // ����������
		case  7: nTemp = RGB(187, 187, 187); break; // ������-�����
		case  8: nTemp = RGB(128, 128, 128); break; // �����
		case  9: nTemp = RGB(66 , 170  , 255); break; // ������-�����

		case 10: nTemp = RGB(144, 238, 144); break; // light green
		case 11: nTemp = RGB(224, 255, 255); break; // light cyan
		case 12: nTemp = RGB(255, 153, 153); break; // light red
		case 13: nTemp = RGB(255, 119, 255); break; // light magenta

		case 14: nTemp = RGB(255, 255, 0  ); break; // ������
		case 15: nTemp = RGB(255, 255, 255); break; // �����
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

//Lab 3
while (true)
{
if(GetAsyncKeyState( VK_SHIFT))
	{
		F = fopen("_Carib256.bmp", "rb");
		//F = fopen("CAT256.BMP", "rb");
		fread(&head_file,sizeof(head_file),1,F);

		unsigned char palitra[256][4];
		fread(&palitra,sizeof(palitra),1,F);
//Print to the screen:
		for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				unsigned char temp= getc(F);
				putpixel(i, j, RGB (palitra [temp][2] ,palitra [temp][1], palitra [temp][0]));
			}

		}
		resize(head_file.biwidth + 9 , head_file.biheight + 9);
		wg->flush();
//END Print to the screen.
fclose(F);
	}

	if(GetAsyncKeyState(VK_CONTROL))
	{
		 F = fopen("_�arib_TC.bmp", "rb");
		//F = fopen("CAT256.BMP", "rb");
		fread(&head_file,sizeof(head_file),1,F);

		unsigned char palitra[256][4];
//fread(&palitra,sizeof(palitra),1,F);
//Print to the screen:
		for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				unsigned char temp1= getc(F);
				unsigned char temp2= getc(F);
				unsigned char temp3= getc(F);
				putpixel(i, j, RGB (temp3 ,temp2, temp1));
			}

		}
		resize(head_file.biwidth + 9 , head_file.biheight + 9);
		wg->flush();
		fclose(F);
	}

//16 color file reading
	if(GetAsyncKeyState(VK_ESCAPE))
	{

		F = fopen("_Carib16.bmp", "rb");
		fread(&head_file,sizeof(head_file),1,F);

		fread(&color_16,sizeof(color_16),1,F);
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
}
//END lab3
}

