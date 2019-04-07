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
	int len;                        // ����� ����
	std::vector < std::string > grid = getExploreData();           // ������� ����
	// ����� ������� lee() ������ grid �������� ���������� WALL � BLANK


	int dx[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
	int dy[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
	int d, i, j, k;


	// ��������������� �����
	d = 0;
	bool stop = false;
	grid[y][x] = d;         // ��������� ������ �������� 0
	do
	{
		stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
		for (i = 0; i < H; ++i)
			for (j = 0; j < W; ++j)
				if (grid[i][j] == d)                         // ������ (x, y) �������� ������ d
				{
					for (k = 0; k < 4; ++k)                    // �������� �� ���� ������������ �������
					{
						int iy = i + dy[k], ix = j + dx[k];
						if (iy >= 0 && iy < H && ix >= 0 && ix < W && (grid[iy][ix] == '.' || grid[iy][ix] == ',' || grid[iy][ix] == '@' || grid[iy][ix] == '$' || grid[iy][ix] == '*'))
						{
							stop = false;              // ������� ������������ ������
							grid[iy][ix] = d + 1;      // �������������� �����
						}
					}
				}
		d++;
	} while (!stop);




	// �������������� ����
	len = grid[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
	d = len;
	j = bx;
	i = by;
	while (d > 0)
	{
		path.push_back(make_pair(i, j));
		// ���������� ������ (x, y) � ����
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = i + dy[k], ix = j + dx[k];
			if (iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == d)
			{
				j = j + dx[k];
				i = i + dy[k];           // ��������� � ������, ������� �� 1 ����� � ������
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