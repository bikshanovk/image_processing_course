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
} head_file, head_file_source ;

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

void main()
{
FILE *F, *F2, *result;
int i, j, x, y;
x=0; y = 767;
//color_16
//color_256;

//Lab 4
while (true)
{
if(GetAsyncKeyState(VK_CONTROL))
	{
		F2 = fopen("QR.bmp", "rb");
		fread(&head_file_source,sizeof(head_file_source),1,F2);

		F = fopen("_сarib_TC.bmp", "rb");
		fread(&head_file,sizeof(head_file),1,F);
		resize(head_file.biwidth + 9 , head_file.biheight + 9);

 //		fread(&palitra,sizeof(palitra),1,F);
//Print to the screen:
	for (j = head_file.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file.biwidth; i++)
			{
				unsigned char temp1= getc(F);
				unsigned char temp2= getc(F);
				unsigned char temp3= getc(F);
				if (j>head_file.biheight-head_file_source.biheight && i<=head_file_source.biwidth) {
				   temp1= getc(F2);
				   temp2= getc(F2);
				   temp3= getc(F2);
				   int temp = ftell(F2);
				   // putpixel(i, j, RGB (0 ,0, 0));
				}
				if (i==142) {
					 //  getc(F2);
					 //  getc(F2);
				   }
				putpixel(i, j, RGB (temp3 ,temp2, temp1));
			}

		}

		fclose(F);   fclose(F2);
	}

		F2 = fopen("QR.bmp", "rb");
		fread(&head_file_source,sizeof(head_file_source),1,F2);

		F = fopen("_сarib_TC.bmp", "rb");
		fread(&head_file,sizeof(head_file),1,F);

//Out for main pic
	int offset = ftell(F);
	j = head_file.biheight-2;
	i = 0;
	while (!feof(F))
	{
			  unsigned char t1= getc(F);
			  unsigned char t2= getc(F);
			  unsigned char t3= getc(F);
			  putpixel(i, j, RGB (t3 ,t2, t1));
			  i++;
			  //Carriage Return:
			  if (i==head_file.biwidth) {
					//Alignment segment:
					offset = ftell(F); 	//Idle
					while ((offset-head_file.bfoffbits) % 4!=0)
					{
						offset=getc(F);	//Idle
						offset = ftell(F); //Idle
					}
					offset = ftell(F);      //Debug
					//END Alignment segment
					i=0;
					j--;
			  }
			  //END Carriage Return
		}

   // putpixel(z, j, RGB (temp3 ,temp2, temp1));
   //  z++;

   fclose(F);

//end out for main pic

 //Output for logo:
	offset = ftell(F2);
	j = head_file_source.biheight-1;
	i = 0;
	while (!feof(F2))
	{
			  unsigned char t1= getc(F2);
			  unsigned char t2= getc(F2);
			  unsigned char t3= getc(F2);
			  putpixel(i, j, RGB (t3 ,t2, t1));
			  i++;
			  //Carriage Return:
			  if (i==head_file_source.biwidth) {
					//Alignment segment:
					offset = ftell(F2); 	//Idle
					while ((offset-head_file_source.bfoffbits) % 4!=0)
					{
						offset=getc(F2);	//Idle
						offset = ftell(F2); //Idle
					}
					offset = ftell(F2);      //Debug
					//END Alignment segment
					i=0;
					j--;
			  }
			  //END Carriage Return
		}
   // putpixel(z, j, RGB (temp3 ,temp2, temp1));
   //  z++;

   fclose(F2);
   //end Output for logo.

	resize(head_file.biwidth, head_file.biheight);
	wg->flush();

   F = fopen("_сarib_TC.bmp", "rb");
   fread  (&head_file_source,sizeof(head_file_source),1,F);

   F2 = fopen("QR.bmp", "rb");
   fread(&head_file,sizeof(head_file),1,F2);

   result = fopen("result.bmp", "wb");
   fwrite(&head_file_source,sizeof(head_file_source),1,result);

   for (j = head_file_source.biheight-1; j >= 0; j--)
		{
			for (i = 0; i < head_file_source.biwidth; i++)
			{
				if (i<head_file.biwidth && j<head_file.biheight)
				{
					fputc(fgetc(F2), result);  fgetc(F);
					fputc(fgetc(F2), result);  fgetc(F);
					fputc(fgetc(F2), result);  fgetc(F);
				} else {
				fputc(fgetc(F), result);
				fputc(fgetc(F), result);
				fputc(fgetc(F), result); }
			}

		}





	fclose(F);
    fclose(F2);
	fclose(result);



}
	}
