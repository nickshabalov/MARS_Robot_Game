#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Robot.h"
#include "Sapper.h"
#include<string>

enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();

	~MainGame();
	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	/// Initializes the level and sets up everything
	void initLevel();

	/// Main game loop for the program
	void gameLoop();

	/// Updates all agents
	void update ();

	void scan();

	/// Renders the game
	void drawGame();

	void collision();

	void checkBorderExploreData();

	/// Member Variables
	RenderWindow m_window; /// The game window

	std::vector<Level*> m_levels; /// vector of all levels (if levels > 1)

	Robot robot;/// Game character

	Sapper sapper; // Или создавть нового каждый раз?

	int m_screenWidth; 

	int m_screenHeight;

	int m_currentLevel;

	GameState m_gameState; /// Play/Exit

	int m_textureSize;

	Clock clock;

	float timer, delay;

	float offsetX = 0, offsetY = 0; /// Camera location

	Font font; //шрифт 

	Text text; //

	sf::Event event;

	int panelSize; /// Size of field with text in the top of the window

	int numApples; /// 

	int scanSteps;

	int iter;

	Sprite s_robot, s_map, s_sapper;

	Image _image;  // или закинуть в робота

	Texture _texture;
};
