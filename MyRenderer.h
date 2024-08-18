#pragma once
#include <iostream>
#include<windows.h>

enum COLOUR{
	FG_BLACK		= 0x0000,
	FG_DARK_BLUE    = 0x0001,
	FG_DARK_GREEN   = 0x0002,
	FG_DARK_CYAN    = 0x0003,
	FG_DARK_RED     = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW  = 0x0006,
	FG_GREY			= 0x0007, // Thanks MS :-/
	FG_DARK_GREY    = 0x0008,
	FG_BLUE			= 0x0009,
	FG_GREEN		= 0x000A,
	FG_CYAN			= 0x000B,
	FG_RED			= 0x000C,
	FG_MAGENTA		= 0x000D,
	FG_YELLOW		= 0x000E,
	FG_WHITE		= 0x000F,
	BG_BLACK		= 0x0000,
	BG_DARK_BLUE	= 0x0010,
	BG_DARK_GREEN	= 0x0020,
	BG_DARK_CYAN	= 0x0030,
	BG_DARK_RED		= 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW	= 0x0060,
	BG_GREY			= 0x0070,
	BG_DARK_GREY	= 0x0080,
	BG_BLUE			= 0x0090,
	BG_GREEN		= 0x00A0,
	BG_CYAN			= 0x00B0,
	BG_RED			= 0x00C0,
	BG_MAGENTA		= 0x00D0,
	BG_YELLOW		= 0x00E0,
	BG_WHITE		= 0x00F0,
};
enum PIXEL_TYPE{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};






class MyRenderer{

public:

int screenwidth;
int screenheight;
HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE); //creates a handle to the window and as parameter i've given it the standard output handle
SMALL_RECT rectwindow;
CHAR_INFO *screenbuffer;//created a pointer to the screen buffer of type CHAR_INFO




int CreateConsole(int width,int height,int fontwidth,int fontheight){


screenwidth=width;
screenheight=height;
rectwindow={0,0,1,1}; //this defines the viewing rectangle of the screen buffer
SetConsoleWindowInfo(hconsole,true,&rectwindow); //why true here? pointers used be aware
COORD BufferEnd={(short)screenwidth,(short)screenheight}; //Defines the coordinates of a character cell in a console screen buffer.The last cell in the buffer in this case.

CONSOLE_FONT_INFOEX FontProperties;//this struct sets the properties of individual character on screen
FontProperties.cbSize=sizeof(FontProperties);
FontProperties.dwFontSize.X=fontwidth;
FontProperties.dwFontSize.Y=fontheight;  //Different properties being set according to the given parameters
FontProperties.FontFamily=FF_DONTCARE;
FontProperties.FontWeight==FW_NORMAL;

//now set the parameters to the different Buffer functions
SetConsoleActiveScreenBuffer(hconsole);
SetConsoleScreenBufferSize(hconsole,BufferEnd);
SetCurrentConsoleFontEx(hconsole,false,&FontProperties); //why false here? pointers used be aware
rectwindow={0,0,(short)screenwidth-1,(short)screenheight-1};
SetConsoleWindowInfo(hconsole,true,&rectwindow); //why true here? pointers used be aware
screenbuffer=new CHAR_INFO[screenwidth*screenheight]; //an array of CHAR_INFO struct {still dont fully understand the new keyword
memset(screenbuffer,0,sizeof(CHAR_INFO)*screenwidth*screenheight);// this sets the memory bytes of screenbuffer to zero (all the bytes that encompass the area of the buffer)






return 1; //The function has to return true
}
void WriteToBuffer(){WriteConsoleOutputW(hconsole,screenbuffer,{(short)screenwidth,(short)screenheight},{0,0},&rectwindow);}
void Draw(int x,int y,short c=0x2588,short col =0x000F){

if (x >= 0&&x<screenwidth&& y>=0 && y<screenheight)
 {
screenbuffer[y * screenwidth + x].Char.UnicodeChar = c;
screenbuffer[y * screenwidth + x].Attributes = col;
}
}
void DrawLine(int x1,int y1,int x2,int y2,short c = 0x2588, short col = 0x000F){
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1; dy = y2 - y1;
		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
        if (dx >= 0)
        { x = x1; y = y1; xe = x2; }
        else
        { x = x2; y = y2; xe = x1;}
        Draw(x, y, c, col);
        for (i = 0; x<xe; i++)
        {
        x = x + 1;
        if (px<0)
        px = px + 2 * dy1;
        else
        {
        if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
        px = px + 2 * (dy1 - dx1);
        }
        Draw(x, y, c, col);
        }
		}
		else
		{
        if (dy >= 0)
        { x = x1; y = y1; ye = y2; }
        else
        { x = x2; y = y2; ye = y1; }
       Draw(x, y, c, col);

        for (i = 0; y<ye; i++)
        {
        y = y + 1;
        if (py <= 0)
        py = py + 2 * dx1;
            else
				{
    if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
    py = py + 2 * (dx1 - dy1);
     }
        Draw(x, y, c, col);
    }
    }
	}
void Clip(int &x, int &y){
if (x < 0) x = 0;
if (x >= screenwidth) x = screenwidth;
if (y < 0) y = 0;
if (y >= screenheight) y = screenheight;
}
void Fill(int x1,int y1,int x2,int y2, short c =0x2588, short col =0x000F){
Clip(x1, y1);
Clip(x2, y2);
for (int x = x1; x < x2; x++)
for (int y = y1; y < y2; y++)
Draw(x, y, c, col);
	}
void FillCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F){
		// Taken from wikipedia
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				Draw(i, ny, c, col);
		};

		while (y >= x)
		{
			// Modified to draw scan-lines instead of edges
			drawline(xc - x, xc + x, yc - y);
			drawline(xc - y, xc + y, yc - x);
			drawline(xc - x, xc + x, yc + y);
			drawline(xc - y, xc + y, yc + x);
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	};

};






/////////////////////////////////////template///////////////////////////////////////////////////////////////

//#include <iostream>
//#include<chrono>
//#include "MyRenderer.h"
//
//
//
//using namespace std;
//
//int screenwidth=256;
//int screenheight=240;
//auto tp1 = chrono::system_clock::now();
//
//
//int main()
//{
// MyRenderer renderer;
// renderer.CreateConsole(screenwidth,screenheight,2,2);
//
//
//while(1)
//{
//
//
//        auto tp2 = std::chrono::system_clock::now();
//        std::chrono::duration<float> elapsedTime = tp2 - tp1;
//        tp1 = tp2;
//        float fElapsedTime = elapsedTime.count();
//        renderer.Fill(0,0,screenwidth,screenheight,PIXEL_SOLID,FG_BLACK);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    renderer.WriteToBuffer();
//}
//
//
//    return 0;
//}



//////////////////////////////////////////////////////////////////////////////