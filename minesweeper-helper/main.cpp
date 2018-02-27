#include <time.h>
#include <iostream>
#include <windows.h>
#include "mouse.h"
#include "screen.h"

using namespace std;

extern int matrix[16][30];
extern int H,W;

int mine_num=0,n_m=0,ret[3][3];
//int mine,_mine=0,_unkown=0,f;
int f;

void get_around_grids(int col,int row,int matr[][30]) //获得待处理值周边的3*3矩阵
{
//	printf("中心值=%d\n",matr[col][row]);
	for(int s=-1;s<2;s++)
	{
		for (int v=-1;v<2;v++)
		{
//			printf("col+s=%d,row+v=%d\n",col+s,row+v);
			if((col+s>=0&&col+s<16)&&(row+v>=0&&row+v<30))
				{ret[s+1][v+1]=matr[col+s][row+v];
//			printf("matrix[col+s][row+v]=%d\n",matr[col+s][row+v]);
			}   
			else
			ret[s+1][v+1]='#';
		}
	}
	return ;
}

/*void printf_ret()  //输出3*3矩阵
{
	for(int t=0;t<3;t++)
	{
		for(int h=0;h<3;h++)
		{
			 printf ("%d",ret[t][h]);
		}
		printf("\n");
	}
	printf("\n");
}*/
/*
bool is_valid(int ret[3][3])
{
	int num_mine=0,num_unkown=0,num=ret[1][1];
	for(int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (ret[i][j] == '*')
            num_mine += 1;
            else if(ret[i][j] == 0)
            num_unkown += 1;
		}
	}
	if (num_mine > num || num_mine + num_unkown < num)
		return false;
	else 
		return true;
}
*/
void main()
{
	char a;
	printf("press any key to continue...");
	std::cin>>a;
	find_offset();
	//get_color(0,0);
	flag(1,1,0);
	flag(4,4,0);
//	Sleep(100); 
	flag(8,8,0);
//	flag(10,15,0);
//	Sleep(500); 
	set_matrix();
	while(mine_num<10)
	{
//		int fg=0;
		get_matrix();
		for(int i=0;i<H;i++)
		{
			n_m=mine_num;
			for(int j=0;j<W;j++)
			{
				int mine,_mine=0,_unkown=0;
	//			int ret[3][3];
				f=matrix[i][j];
//				printf("待处理数字f=%d\n",f);
				if(0<f&&f<7)
				{
				  get_around_grids(i,j,matrix);
//				  printf_ret();
				  mine=ret[1][1];
//				  printf("雷的个数=%d\n",mine);
				  for(int l=0;l<3;l++)
				    {
					  for(int k=0;k<3;k++)
					   {
//						   printf("ret[%d][%d]=%d\n",l,k,ret[l][k]);
						  if(ret[l][k]==0)
							 { _unkown+=1;
//						  printf("未知是啥个数=%d\n",_unkown);
						  }
						  if(ret[l][k]==42)
							{  _mine+=1;
//						  printf("已知雷个数=%d\n",_mine);
						  }
					   }
				    }
				  if(mine<_unkown+_mine&&mine==_mine)
				  {
					  for(int x=0;x<3;x++)
				      {
					    for(int y=0;y<3;y++)
					     {
		//				 printf_ret();
						  if(ret[x][y]==0)
							{ flag(1,1,0);
						  flag(i-1+x,j-1+y,0); }
					    }
				     }
		//			  fg=1;
				  }
				  else if(mine==_unkown+_mine&&mine!=_mine)
				  {
					  for(int x=0;x<3;x++)
				      {
					    for(int y=0;y<3;y++)
					     {
		//					 printf_ret();
						  if(ret[x][y]==0)
							{ flag(1,1,0);
							 flag(i-1+x,j-1+y,1); 
						     mine_num+=1;
							 Sleep(100);}
					    }
				     }
					  j=j+3;
//					  fg=1;
				  }
				}
//				if(fg==1)
//				{
//					i=H;
//					j=W;
//				}
			}
			if(n_m<mine_num)
				{
//					n_m=mine_num;
					i=i+3;
				}
		}
	}
	printf("Congratulations, find all mines");
}