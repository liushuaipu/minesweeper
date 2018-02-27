#include <stdlib.h>
#include <Windows.h>  
#include <iostream>
#include "screen.h"

using namespace std;

extern long int _base[2];

void flag(int col,int row,bool is_mine)
  {
	  long int x[2];
	  get_base_xy(col,row);
	  x[0]=_base[0];
	  x[1]=_base[1];
//	  printf("x[%ld,%ld]\n",x[0],x[1]);
	  x[0]+=8;
	  x[1]+=8;
	  SetCursorPos(x[0],x[1]);
//	  printf("鼠标当前坐标x=%d,y=%d\n",x[0],x[1]);
	  if (is_mine==0)
		 { 
			 mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
	     }
	  else
	    {
			 mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
	    }
       SetCursorPos(0,1);
  } 