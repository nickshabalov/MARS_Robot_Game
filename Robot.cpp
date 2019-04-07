#include "Robot.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include<iostream>

using namespace sf;
using namespace std;
Robot::Robot() :
	x(1), y(1), m_exploreDataHeight(10), m_exploreDataWidht(10), _mode(RobotMode::MANUAL), numSteps(0), dir(' ')
{
	m_exploreData.resize(m_exploreDataHeight);
	for (int i = 0; i < m_exploreDataHeight; i++)
	{
		m_exploreData[i].resize(m_exploreDataWidht);
		for (int j = 0; j < m_exploreDataWidht; j++)
		{
			m_exploreData[i][j] = ' ';
		}
	}

}



Robot::~Robot()
{
	// Don't forget to delete the levelData!
	for (int i = 0; i < (int)m_exploreData.size(); i++)
	{
		m_exploreData[i] = "";
	}
}

void Robot::move()  ///change it
{
	lastX = x;
	lastY = y;

	if (Keyboard::isKeyPressed(Keyboard::Left) || dir == 'L')
	{
		x -= 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) || dir == 'R')
	{
		x += 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) || dir == 'U')
	{
		y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || dir == 'D')
	{
		y += 1;
	}
	if (_mode == RobotMode::AUTO)
	{
		x = path.back().second;
		y = path.back().first;
		path.pop_back();
	}
	
}

void Robot::lastPosition()
{
	x = lastX;
	y = lastY;
}

bool Robot::grab()
{
	if (Keyboard::isKeyPressed(Keyboard::A) || _mode == RobotMode::AUTO)
	{
		return true;
	}
	return false;
}

bool Robot::scan()
{
	if (Keyboard::isKeyPressed(Keyboard::F) || _mode == RobotMode::SCAN)
	{
		return true;
	}
	return false;

}

void Robot::setMode()
{
	if (Keyboard::isKeyPressed(Keyboard::S))
	{

		mode = (mode + 1) % 3;
		switch (mode)
		{
		case 0:
			_mode = RobotMode::MANUAL;
			dir = ' ';
			appleData.clear();
			break;
		case 1:
			_mode = RobotMode::SCAN;
			numSteps = 100;
			 dir = 'U';
			break;
		case 2:
			_mode = RobotMode::AUTO;
			dir = ' ';
			if (!exploreAppleData())
			{
				_mode = RobotMode::MANUAL;
				mode = (mode + 1) % 3;
			}
			break;
		default:
			break;
		}
	}
}



void Robot::setExploreData(int x, int y, char c)
{
			m_exploreData[y][x] = c;
}

void Robot::resizeExploreData(char dir)
{
	//resize up/down/left/right
	std::vector <std::string> _temp;

	switch (dir)
	{
	case 'U':
		//up
		m_exploreDataHeight = m_exploreDataHeight * 2;
		_temp.resize(m_exploreDataHeight);
		for (int i = 0; i < m_exploreDataHeight / 2; i++)
		{
			_temp[i].resize(m_exploreDataWidht);
			for (int j = 0; j < m_exploreDataWidht; j++)
			{
				_temp[i][j] = ' ';
			}
		}
		for (int i = m_exploreDataHeight / 2; i < m_exploreDataHeight; i++)
		{
			_temp[i].resize(m_exploreDataWidht);
			for (int j = 0; j < m_exploreDataWidht; j++)
			{
				_temp[i][j] = m_exploreData[i - (m_exploreDataHeight / 2)][j];
			}
		}
		break;
	case 'D':
//down
	m_exploreDataHeight = m_exploreDataHeight * 2;
	_temp.resize(m_exploreDataHeight);
	for (int i = 0; i < m_exploreDataHeight / 2; i++)
	{
		_temp[i].resize(m_exploreDataWidht);
		for (int j = 0; j < m_exploreDataWidht; j++)
		{
			_temp[i][j] = m_exploreData[i][j];
		}
	}
	for (int i = m_exploreDataHeight / 2; i < m_exploreDataHeight; i++)
	{
		_temp[i].resize(m_exploreDataWidht);
		for (int j = 0; j < m_exploreDataWidht; j++)
		{
			_temp[i][j] = ' ';
		}
	}
	
	
	break;
	case 'L':

	//left
	m_exploreDataWidht = m_exploreDataWidht * 2;
	_temp.resize(m_exploreDataHeight);
	for (int i = 0; i < m_exploreDataHeight; i++)
	{
		_temp[i].resize(m_exploreDataWidht);
		for (int j = 0; j < m_exploreDataWidht / 2; j++)
		{
			_temp[i][j] = ' ';
		}
		for (int j = m_exploreDataWidht / 2; j < m_exploreDataWidht; j++)
		{
			_temp[i][j] = m_exploreData[i][j - (m_exploreDataWidht / 2)];
		}
	}
	break;
	case 'R':

	//right
	m_exploreDataWidht = m_exploreDataWidht * 2;
	_temp.resize(m_exploreDataHeight);
	for (int i = 0; i < m_exploreDataHeight; i++)
	{
		_temp[i].resize(m_exploreDataWidht);
		for (int j = 0; j < m_exploreDataWidht / 2; j++)
		{
			_temp[i][j] = m_exploreData[i][j];
		}
		for (int j = m_exploreDataWidht / 2; j < m_exploreDataWidht ; j++)
		{
			_temp[i][j] = ' ';
		}
	}
	break; 
		throw "No such direction to resize , choose U/D/R/L";
		break;
	}
	 
	m_exploreData = _temp;
}

RobotMode Robot::getRobotMode() const //?����� �������� �� �����
{
	if (_mode == RobotMode::MANUAL)
	{
		return RobotMode::MANUAL;
	}
	if (_mode == RobotMode::SCAN)
	{
		return RobotMode::SCAN;
	}
	if (_mode == RobotMode::AUTO)
	{
		return RobotMode::AUTO;
	}
}

string Robot::outRobotMode() const
{
	if (_mode == RobotMode::MANUAL)
	{
		return "MANUAL";
	}
	if (_mode == RobotMode::SCAN)
	{
		return "SCAN";
	}
	if (_mode == RobotMode::AUTO)
	{
		return "AUTO";
	}
}

void Robot::step()
{
	if (numSteps > 0)
	{
		numSteps--;
	}
	else if(numSteps == 0)
	{
		_mode = RobotMode::MANUAL;
		dir = ' ';
		mode = (mode + 1) % 3;
	}
}

void Robot::next_step()
{
	
	if (getExploreData()[getY() - 1][getX()] == '.' || getExploreData()[getY() - 1][getX()] == '@')
	{
		dir = 'U';
	}
	else if (getExploreData()[getY()][getX() + 1] == '.' || getExploreData()[getY()][getX() + 1] == '@')
	{
		dir = 'R';
	}
	else if (getExploreData()[getY()][getX() - 1] == '.' || getExploreData()[getY()][getX() - 1] == '@')
	{
		dir = 'L';
	}
	else if (getExploreData()[getY() + 1][getX()] == '.' || getExploreData()[getY() + 1][getX()] == '@')
	{
		dir = 'D';
	}
	else
	{
		dir = ' ';
	}
}

void Robot::setNumSteps(int num_steps)
{
	numSteps = num_steps;
}

bool Robot::exploreAppleData()
{
	appleData.clear();
	for (int i = 0; i < m_exploreDataHeight; i++)
	{
		for (int j = 0; j < m_exploreDataWidht; j++)
		{
			if (m_exploreData[i][j] == '@' || m_exploreData[i][j] == '$')
			{
				appleData.push_back(make_pair(i, j));
			}
		}
	}
	if (!appleData.empty())
	{
		return true;
	}
	return false;
}

void Robot::AutoEnd()
{
	_mode = RobotMode::MANUAL;
	mode = (mode + 1) % 3;
}

bool Robot::EmptyPath()
{
	if (path.empty())
	{
		return true;
	}
	return false;
}



bool Robot::algoritm()
{
	int H = getExploreDataHeight();
	int W = getExploreDataWidht();
	int bx = appleData[0].second;
	int by = appleData[0].first;
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
						if (iy >= 0 && iy < H && ix >= 0 && ix < W && (grid[iy][ix] == '.' || grid[iy][ix] == ',' || grid[iy][ix] == '@' || grid[iy][ix] == '$'))
						{
							stop = false;              // ������� ������������ ������
							grid[iy][ix] = d + 1;      // �������������� �����
						}
					}
				}
		d++;
	} while (!stop );


  

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
	appleData.erase(appleData.begin());
	return true;
}

