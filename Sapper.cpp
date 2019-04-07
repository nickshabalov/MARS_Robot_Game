#include "Sapper.h"
#include <fstream>
#include<iostream>
#include<string>
#include<vector>
#include<functional>



using namespace std;

Sapper::Sapper()
{
	x = 1;
	y = 1;
}


Sapper::~Sapper()
{
}

std::string Sapper::outRobotMode() const
{
	if (SapperMode)
	{
		return "ON";
	}
	else
	{
		return "OFF";
	}
}

void Sapper::setMode()
{

	if (Keyboard::isKeyPressed(Keyboard::H))
	{
		if (SapperMode)
		{
			SapperMode = false;
		}
		else
		{
			SapperMode = true;
		}
	}
}


bool Sapper::algoritm()
{
	int H = getExploreDataHeight();
	int W = getExploreDataWidht();
	int bx = minesData[0].second;
	int by = minesData[0].first;
	int len;                        // длина пути
	std::vector < std::string > grid = getExploreData();           // рабочее поле
	// ѕеред вызовом lee() массив grid заполнен значени€ми WALL и BLANK


	int dx[4] = { 1, 0, -1, 0 };   // смещени€, соответствующие сосед€м €чейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int d, i, j, k;


	// распространение волны
	d = 0;
	bool stop = false;
	grid[y][x] = d;         // стартова€ €чейка помечена 0
	do
	{
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (i = 0; i < H; ++i)
			for (j = 0; j < W; ++j)
				if (grid[i][j] == d)                         // €чейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным сосед€м
					{
						int iy = i + dy[k], ix = j + dx[k];
						if (iy >= 0 && iy < H && ix >= 0 && ix < W && (grid[iy][ix] == '.' || grid[iy][ix] == ',' || grid[iy][ix] == '@' || grid[iy][ix] == '$' || grid[iy][ix] == '*'))
						{
							stop = false;              // найдены непомеченные клетки
							grid[iy][ix] = d + 1;      // распростран€ем волну
						}
					}
				}
		d++;
	} while (!stop);




	// восстановление пути
	len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
	d = len;
	j = bx;
	i = by;
	while (d > 0)
	{
		path.push_back(make_pair(i, j));
		// записываем €чейку (x, y) в путь
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = i + dy[k], ix = j + dx[k];
			if (iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == d)
			{
				j = j + dx[k];
				i = i + dy[k];           // переходим в €чейку, котора€ на 1 ближе к старту
				break;
			}
		}
	}
	minesData.erase(minesData.begin());
	return true;
}

bool Sapper::exploreMinesData()
{
	minesData.clear();
	for (int i = 0; i < getExploreDataHeight(); i++)
	{
		for (int j = 0; j < getExploreDataWidht(); j++)
		{
			if (getExploreData()[i][j] == '*')
			{
				minesData.push_back(make_pair(i, j));
			}
		}
	}
	if (!minesData.empty())
	{
		return true;
	}
	return false;
}

bool Sapper::EmptyPath()
{
	if (path.empty())
	{
		return true;
	}
	return false;
}

void Sapper::AutoEnd()
{
	SapperMode = false;
}

void Sapper::move()  ///change it
{
	
	lastX = x;
	lastY = y;
		x = path.back().second;
		y = path.back().first;
		path.pop_back();

}