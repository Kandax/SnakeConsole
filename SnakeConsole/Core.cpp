#include "Core.h"

Core::Core(int w, int h, int fW, int fH)
{
	width = 120;
	height = 40;
	m_bufScreen = new CHAR_INFO[w * h];
	m_rectWindow = { 0,0,(short)width,(short)height };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);
	setFontSize(fW, fH);
	srand(time(NULL));
	SetConsoleTitle("Snake");
	for (int i = 0; i <= snakeSize; i++) {
		parts.push_back(part());
		partsOldPos.push_back(partOldPos());
	}
		
	loop();
	
	
}

void Core::loop()
{
	
	while (run) {
		events();
		update();
		render();
	}
}

void Core::events()
{
	//FPS start
	fps.start(); 
	
	/////////////Get input////////////
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
		if (dir != 1) dir = 0;
	}
	else if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
		if (dir != 0) dir = 1;
	}

	else if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
		if (dir != 3) dir = 2;
	}
	else if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
		if (dir != 2) dir = 3;
	}


}

void Core::update()
{
	/////////////player movement/////////////
	{
		for (int i = 0; i < parts.size(); i++) {
			if (i == 0) {
				if (dir == 0) {//Down
					if (m_bufScreen[(parts[0].y + parts[0].sizeY) * width + parts[0].x].Attributes == FG_GREY)
					{
						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[(parts[0].y + parts[0].sizeY) * width + parts[0].x].Attributes == FG_GREEN) {
						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[(parts[0].y + parts[0].sizeY) * width + parts[0].x].Attributes == FG_RED) {
						parts.push_back(part());
						partsOldPos.push_back(partOldPos());
						
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].y += 2;

						foodRandPos(2, width - 1, 1, height);
					}
					else {
						
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].y += 2;


					}
				}
				if (dir == 1) {//Up
					if (m_bufScreen[(parts[0].y - 1) * width + parts[0].x].Attributes == FG_GREY) {
						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[(parts[0].y - 1) * width + parts[0].x].Attributes == FG_GREEN) {
						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[(parts[0].y - 1) * width + parts[0].x].Attributes == FG_RED) {
						parts.push_back(part());
						partsOldPos.push_back(partOldPos());
						
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].y -= 2;

						foodRandPos(2, width - 1, 1, height);
					}
					else {
						
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].y -= 2;

					}
				}
				if (dir == 2) {//Right

					if (m_bufScreen[parts[0].y * width + (parts[0].x + parts[0].sizeX)].Attributes == FG_GREY) {
						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[parts[0].y * width + (parts[0].x + parts[0].sizeX)].Attributes == FG_GREEN) {						
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[parts[0].y * width + (parts[0].x + parts[0].sizeX)].Attributes == FG_RED) {
						parts.push_back(part());
						partsOldPos.push_back(partOldPos());
						//Sleep(100);
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].x += 4;

						foodRandPos(2, width - 1, 1, height);
					}
					else {
						
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].x += 4;

					}
				}
				if (dir == 3) {//Left
					if (m_bufScreen[parts[0].y * width + (parts[0].x - 1)].Attributes == FG_GREY) {
						//Sleep(100);
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[parts[0].y * width + (parts[0].x - 1)].Attributes == FG_GREEN) {
						//Sleep(100);
						run = false;
						setFontSize(16, 16);
					}
					else if (m_bufScreen[parts[0].y * width + (parts[0].x - 1)].Attributes == FG_RED) {
						//parts.push_back(part());
						//partsOldPos.push_back(partOldPos());
						//
						//Sleep(100);
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].x -= 4;
						//
						foodRandPos(2,width -1,1,height);
					
					}
					else {
						//Sleep(100);
						partsOldPos[i].x = parts[i].x;
						partsOldPos[i].y = parts[i].y;
						parts[i].x -= 4;

					}

				}


			}
			else {
				partsOldPos[i].x = parts[i].x;
				partsOldPos[i].y = parts[i].y;
				parts[i].x = partsOldPos[i - 1].x;
				parts[i].y = partsOldPos[i - 1].y;
			}



		}
	}
	



}

void Core::render()
{
	//board
	fill(0,0 , width, height, PIXEL_SOLID,FG_DARK_GREY);
	for (int i = 0; i <height; i++) {
		for (int j = 0; j < width; j++) {
			if ((i == 0) || (i == height - 1)) {
				draw(j, i, PIXEL_SOLID, FG_GREY);
			}
			else if ((j == 0) || (j == width-2) ) {
				draw(j, i, PIXEL_SOLID, FG_GREY);
				draw(j + 1, i, PIXEL_SOLID, FG_GREY);
			}
			
		}
	}
	//Food
	fill(foods.x, foods.y, foods.sizeX, foods.sizeY, foods.mark, foods.color);


	//player
	for (int i = 0; i < parts.size(); i++) {
		if (i == 0) {
			parts[i].color = FG_DARK_GREEN;
		}
		else {
			parts[i].color = FG_GREEN;
		}
		fill(parts[i].x, parts[i].y, parts[i].sizeX, parts[i].sizeY, parts[i].mark,parts[i].color);
	}
	
	//Render Console
	WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)width,(short)height }, { 0,0 }, &m_rectWindow);

	//Fps stop
	fps.end();
	
	
}

void Core::setFontSize(int a, int b)
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(m_hConsole, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetConsoleTextAttribute(m_hConsole, 0x0000);
	SetCurrentConsoleFontEx(m_hConsole, 0, lpConsoleCurrentFontEx);

} 

void Core::draw(int x, int y, short c, short col)
{
	m_bufScreen[y * width + x].Attributes = col;
	m_bufScreen[y * width + x].Char.UnicodeChar = c;
	
}

void Core::fill(int x, int y, int w, int h, short c, short col)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			draw(x + j, y + i, c, col);
		}
	}


}

void Core::foodRandPos(int minX, int maxX, int minY, int maxY)
{
	int rangeX;
	int rangeY;


	minX = 2;
	maxX = width - 1;
	rangeX = (maxX - minX) / 4;
	int rndX = minX + ((rand() % rangeX) * 4);

	minY = 1;
	maxY = height;
	rangeY = (maxY - minY) / 2;;
	int rndY = minY + ((rand() % rangeY) * 2);

	foods.x = rndX;
	foods.y = rndY;


}

