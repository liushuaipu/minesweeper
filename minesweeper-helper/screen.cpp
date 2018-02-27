#include <iostream>
#include <time.h>
#include <Windows.h>  
#include "screen_capture.h"
#include "screen.h"

using namespace std;

long int offset[2];
HWND wnd;
int W=9,H=9;
int _color[3],s=16;
int matrix[16][30];
long int _base[2];

void find_offset()
{
	if (offset[2]==NULL)
	    wnd=::FindWindow(NULL,L"扫雷");
//	    printf("扫雷窗口句柄=%ld\n",wnd);
	    RECT rect;
		::GetWindowRect(wnd,&rect);
//		printf("left=%d,right=%d,top=%d,bottom=%d\n",rect.left,rect.right,rect.top,rect.bottom);
		offset[0]=rect.left+15;
		offset[1]=rect.top+100;
//		printf("第一格左上角坐标=%d，y=%d\n",offset[0],offset[1]);	
	return ;
}

void get_base_xy(int col,int row)
{
//	find_offset();
    _base[0]=row*s+offset[0];
	_base[1]=col*s+offset[1];
//	printf("第%d行%d列的上角坐标x=%d，y=%d\n",col,row,_base[0],_base[1]);
	return ;
}

void set_matrix()
{
  for (int i=0;i<H;i++)
   {
	 for (int j=0;j<W;j++)
		matrix[i][j]=0;
    }
}

void get_matrix()
{
  // time_t t1 = time(0);
   HWND hWnd=::GetDesktopWindow();
   HDC hdc=::GetDC(NULL);
 //  time_t t2 = time(0);
  
   int col,row;
/*   for (int i=0;i<H;i++)
    {
		for (int j=0;j<W;j++)
		    matrix[i][j]=0;
    }*/
  for (col=0;col<H;col++)
   {
        for(row=0;row<W;row++)
		{
			if (matrix[col][row]!=0)
			  {
//				  printf("matrix[%d][%d]非零\n",col,row);
				  continue;
			  }
			long int base_x,base_y;
			 get_base_xy(col,row);
			 base_x=_base[0];
			 base_y=_base[1];
			int _y;
			COLORREF pixel;
//			printf("判断点的坐标x=%d,y=%d\n",base_x,base_y+5);
			pixel = ::GetPixel(hdc,base_x,base_y+5);
			BYTE a = GetRValue(pixel);
//			printf("像素R=%d\n",a);
			if (a==255)                           //判断是否未点开
			{
					pixel = ::GetPixel(hdc,base_x+7,base_y+11);
                    BYTE c = GetRValue(pixel)>>4;
					BYTE e = GetGValue(pixel)>>4;
					BYTE u = GetBValue(pixel)>>4;
                    if (c==0&&e==0&&u==0)
					 matrix[col][row]='*';    //是雷，矩阵标记为 *
					else 
					{matrix[col][row]=0;}     //否则为 0
//					printf("matrix[%d][%d]=%d\n",col,row,matrix[col][row]);
			}
			else
			{
				for(_y=4;_y<s-4;_y++)
					{
						pixel = ::GetPixel(hdc,base_x+_y,base_y+_y);
                        BYTE r = GetRValue(pixel);
                        BYTE g = GetGValue(pixel);
                        BYTE b = GetBValue(pixel);
//						printf("像素原RGB=%d,%d,%d\n",r,g,b);
						_color[0]=r>>4;
						_color[1]=g>>4;
						_color[2]=b>>4;
	//				    _color[r>>4,g>>4,b>>4];
///						printf("右移四位后RGB=%d,%d,%d\n",_color[0],_color[1],_color[2]);
						if (_color[0]==0&&_color[1]==0&&_color[2]==15){
						matrix[col][row]=1;break;
						}else if (_color[0]==0&&_color[1]==8&&_color[2]==0){
						matrix[col][row]=2;break;
						}else if (_color[0]==15&&_color[1]==0&&_color[2]==0){
						matrix[col][row]=3;break;
						}else if (_color[0]==0&&_color[1]==0&&_color[2]==8){
						matrix[col][row]=4;break;
						}else if (_color[0]==8&&_color[1]==0&&_color[2]==0){
						matrix[col][row]=5;break;
						}else if (_color[0]==0&&_color[1]==8&&_color[2]==8){
						matrix[col][row]=6;break;
						}
						//else {
						//	matrix[col][row]='#';}
					}
				if(matrix[col][row]==0)
					{
						matrix[col][row]='#';
				    }
//						printf("matrix[%d][%d]=%d\n",col,row,matrix[col][row]);
			}
      }
   }
//    print_matrix(matrix);
  //  time_t t3 = time(0);
	//printf("截图耗时 %.2fs, 识别耗时 %.2fs\n", t2 - t1, t3 - t2);
    return ;
}

/*void print_matrix(int mat[16][30])
{
	for (int i=0;i<H;i++)
	{
		for (int j=0;j<W;j++)
		{
		  printf ("%d",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}*/
/*
void get_color(int i,int j)
{
	   HWND hWnd=::GetDesktopWindow();
       HDC hdc=::GetDC(NULL);
			long int c1,c2;
			 get_base_xy(i,j);
			 c1=_base[0];
			 c2=_base[1];
			COLORREF pixel;
			printf("起点坐标x=%d,y=%d\n",c1,c2);
		//	for(int c=0;c<16;c++)                           
		//	{
		//		for(int d=0;d<16;d++)
		//		{
					pixel = ::GetPixel(hdc,c1+7,c2+11);
                    BYTE r = GetRValue(pixel);
					BYTE g = GetGValue(pixel);
					BYTE b = GetBValue(pixel);
					printf("R=%d,G=%dB=%d\n",r,g,b);
		//		}
		//	}
}*/