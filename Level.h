#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "SpriteBatch.h"

using namespace sf;

class Level
{
public:
	//Load the level
	Level(const std::string& fileName);
	
	~Level();

	int getWidth() const { return _levelData[0].size(); }

	int getHeight() const { return _levelData.size(); }

	int getNumMines() const { return _numMines; }

	int getNumApples() const { return _numApples; }

	Image getImage() const { return _image; }

	Texture getTexture() const { return _texture; }

	std::vector < std::string > getLevelData() const { return _levelData; }
	
	Sprite s_map;

	void takeApple(int x, int y);

private:

	std::vector <std::string> _levelData;

	int _numMines;

	int _numApples;
	 
	Image _image;

	Texture _texture;
};

