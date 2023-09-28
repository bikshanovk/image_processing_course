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


typedef struct TPCXHeaderStruct
 {
  unsigned char ID;  //Постоянный флаг 10 = ZSoft .PCX
  unsigned char Version; // Информация о версии
  unsigned char Coding; //1 = PCX кодирование RLE
  unsigned char BitPerPixel; // Число бит на пиксел
  unsigned int  XMin; // Размеры изображения
  unsigned int  YMin;
  unsigned int  XMax;
  unsigned int  YMax;
  unsigned int  HRes; // Горизонтальное разрешение создающего устройства
  unsigned int  VRes; // Вертикальное разрешение создающего устройства
  unsigned char Palette[48]; // Набор цветовой палитры (для 16-цветного изображения)
  unsigned char Reserved;
  unsigned char Planes; // Число цветовых слоев
  unsigned int  BytePerLine; // Число байт на строку в цветовом слое (для PCX-файлов всегда должно быть четным)
  unsigned int  PaletteInfo; // Как интерпретировать палитру:
//1 = цветная/черно-белая,
//2 = градации серого
  unsigned int  HScreenSize;
  unsigned int  VScreenSize;
  unsigned char Filler[54]; // Заполняется нулями до конца заголовка
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
