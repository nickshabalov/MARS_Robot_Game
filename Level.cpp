#include "Level.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

Level::Level(const std::string& fileName)
{

	ifstream file;
	file.open(fileName);

	//Error checking
	if (file.fail())
	{
		throw "Failed to open file!";
	}

	//Throw away the first strig in temp
	string temp = "";
	/*file >> temp >> _numMines;*/

	while (getline(file, temp))
	{
		_levelData.push_back(temp);
	}

	file.close();
}


Level::~Level()
{
	// Don't forget to delete the levelData!
	for (int i = 0; i < (int)_levelData.size(); i++)
	{
		_levelData[i] = "";
	}
}


//Change the Mars map
void Level::takeApple(int x, int y)
{
		_levelData[y][x] = '.';
}


		



