#pragma once
#include <windows.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include "Fps.cpp"


enum PIXEL_TYPE {
	PIXEL_SOLID = 219,
	PIXEL_THREEQUARTERS = 178,
	PIXEL_HALF = 177,
	PIXEL_QUARTER = 176 ,
};
enum COLOUR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, 
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};
 

struct part {
	int x = 18;
	int y = 5;
	int sizeX = 4;
	int sizeY = 2;
	short mark = PIXEL_SOLID;
	short color = FG_GREEN;
};
struct partOldPos {
	int x = 18;
	int y = 5;
};

struct food {
	int x = 38;
	int y = 1;
	int sizeX = 4;
	int sizeY = 2;
	short mark = PIXEL_SOLID;
	short color = FG_RED;
};



class Core
{
public:
	Core(int w, int h, int fW,int fH);
	void loop();
protected:
	int width;
	int height;
	HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT m_rectWindow;
	CHAR_INFO* m_bufScreen;
	
	int dir = 0;
	bool run = true;
	int snakeSize = 2;
	food foods;

	std::vector<part> parts;
	std::vector<partOldPos> partsOldPos;

	Fps fps;

	void events();
	void update();
	void render();
	void setFontSize(int a, int b);
	void draw(int x=0, int y = 0, short c = 0x49DB, short col = 0x000F);
	void fill(int x = 0, int y = 0, int w = 1, int h = 1, short c = 0x49DB, short col = 0x000F);
	void foodRandPos(int minX , int maxX , int minY , int maxY );
	


	
	

};

