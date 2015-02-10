// HMaps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct MAP
{
	float map[128][64];
}
;

void DiamondH(int ax,int ay,int bx,int by,MAP& it);
void DiamondV(int ax, int ay, int bx, int by, MAP& it);
void Square(int ax, int ay, int bx, int by, MAP& it);
void DiamondSquare(int ax, int ay, int bx, int by, MAP& it);

int _tmain(int argc, _TCHAR* argv[])
{
	std::srand(time(0));
	MAP terra;
	for (int i = 0; i < 128; i++)
	{
		for (int k = 0; k < 64; k++)
		{
			terra.map[i][k] = 0;
		}
	}
	terra.map[0][0] = std::rand() % 255 /255.0;
	terra.map[0][63] = std::rand() % 255 / 255.0;
	terra.map[127][0] = std::rand() % 255 / 255.0;
	terra.map[127][63] = std::rand() % 255 / 255.0;
	DiamondSquare(0, 0, 64, 128, terra);
	return 0;
}

void DiamondH(int ax, int ay, int bx, int by, MAP& it)
{

	int cx = ax;
	int cy = ay;
	int dx = (bx + ax) / 2;
	int dy = (ay+(ay - by) / 2) % 128;
	int fx = bx;
	int fy = ay;
	int ex = dx;
	int ey = (by+(by - ay) / 2) % 128;
	return;
}

void Square(int ax, int ay, int bx, int by, MAP& it)
{
	float height = (it.map[ay][ax] + it.map[ay][bx] + it.map[by][ax] + it.map[by][bx]) / 4;
	height += std::rand() % 255 / 255.0;
	int x = (bx + ax) / 2;
	int y = (by + ay) / 2;
	it.map[y][x] = height;
	return;
}