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


typedef struct TPCXHeaderStruct
 {
  unsigned char ID;  //���������� ���� 10 = ZSoft .PCX
  unsigned char Version; // ���������� � ������
  unsigned char Coding; //1 = PCX ����������� RLE
  unsigned char BitPerPixel; // ����� ��� �� ������
  unsigned int  XMin; // ������� �����������
  unsigned int  YMin;
  unsigned int  XMax;
  unsigned int  YMax;
  unsigned int  HRes; // �������������� ���������� ���������� ����������
  unsigned int  VRes; // ������������ ���������� ���������� ����������
  unsigned char Palette[48]; // ����� �������� ������� (��� 16-�������� �����������)
  unsigned char Reserved;
  unsigned char Planes; // ����� �������� �����
  unsigned int  BytePerLine; // ����� ���� �� ������ � �������� ���� (��� PCX-������ ������ ������ ���� ������)
  unsigned int  PaletteInfo; // ��� ���������������� �������:
//1 = �������/�����-�����,
//2 = �������� ������
  unsigned int  HScreenSize;
  unsigned int  VScreenSize;
  unsigned char Filler[54]; // ����������� ������ �� ����� ���������
 } TPCXHeader;


void main()
{
FILE *F;
int i, j, x, y;
TPCXHeader head;
//Lab 5
F = fopen("_Carib256.pcx", "rb");


char header[128];
unsigned char palette[792];
F = fopen("_Carib256.pcx", "rb");
fread  (&header, 1, 128, F);
//int x, y;

 /* Get the top left x and y */
memcpy( &x, &header[4], 2 );
memcpy( &y, &header[6], 2 );
int w, h;
/* Get the width and height */
  memcpy( &w, &header[8], 2 );
  memcpy( &h, &header[10], 2 );

  resize(w+9, h+9);

  fseek(F,-769L,SEEK_END);
  unsigned char c, runlen;
  c = fgetc(F);

  fread( &palette, 1, 768, F );

	fseek(F,128L,SEEK_SET);

	int drawing = 1;
	x=0; y=0;

  while (drawing)
  {
	c=fgetc(F);
	if ((int)c>=192)
	{
	   int amount =  (int)c % 192;
	   c=fgetc(F);
	   for (i = 0; i < amount; i++)
	   {
		   putpixel(x, y, RGB( palette[c*3], palette[c*3+1], palette[c*3+2]));
		   x++; if (x==1024)
		   {
			   x=0; y++;
		   }
	   }
	} else
	{
	   putpixel(x, y, RGB( palette[c*3], palette[c*3+1], palette[c*3+2]));
	   x++; if (x==1024)
		   {
			   x=0; y++;
		   }
	}
	if (y==767)
	{
	   drawing=0;
	}
  }

 wg->flush();
 fclose(F);
//END Lab5

}
