
#include "MainGame.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <sstream>
#include <string>

using namespace sf;

MainGame::MainGame() :
	m_screenWidth(768),
	m_screenHeight(512),
	m_gameState(GameState::PLAY),
	m_textureSize(16),
	timer(0),
	delay(0.1),
	panelSize(50),
	numApples(0),
	scanSteps(0),
	iter(0)
{
	// Empty
	

}

MainGame::~MainGame() 
{
	// Don't forget to delete the levels!
	for (int i = 0; i < (int)m_levels.size(); i++)
	{
		delete m_levels[i];
	}
	
}

void MainGame::run() 
{

	initSystems();

	initLevel();

	gameLoop();
}


void MainGame::initSystems()
{
	srand(time(0));
	// Create our window
	m_window.create(VideoMode(m_screenWidth, m_screenHeight), "Proton!");

}

void MainGame::initLevel()
{
	// Level 1
	m_levels.push_back(new Level("level.txt"));
	m_currentLevel = 0;
	
	/*robot.*/s_robot.setPosition(robot.getX()*m_textureSize,panelSize + robot.getY() * m_textureSize);


	/*sapper.s_robot.setPosition(sapper.getX()*m_textureSize, panelSize + sapper.getY() * m_textureSize);*/

	font.loadFromFile("ARIAL.TTF");
	text.setFont(font); 

	// set the color
	text.setFillColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold);


	_image.loadFromFile("_texture.png");
	_texture.loadFromImage(_image);

	s_robot.setTexture(_texture);
	s_robot.setTextureRect(IntRect(48, 0, 16, 16));
	s_sapper.setTexture(_texture);
	s_sapper.setTextureRect(IntRect(80, 0, 16, 16));
	s_map.setTexture(_texture);
	s_map.setTextureRect(IntRect(16, 0, 16, 16));


}


void MainGame::gameLoop() 
{
	
	while (m_window.isOpen())
	{
		//Exit the programm
		std::string  a;
		istringstream iss(a, istringstream::in);
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				m_window.close();

			/*if (event.type == Event::TextEntered)
			{
				
				if ((event.text.unicode >= 48 && event.text.unicode <= 57 ) || event.text.unicode == 13)
				{
					cout << (char)event.text.unicode;
					while (event.text.unicode == 13)
					{
						a[iter] = (char)event.text.unicode;
						iter++;
						cout << iter;
					}
					iter = 0;
					
				}
				iss>> scanSteps;
				cout << scanSteps;
				robot.setNumSteps(scanSteps);
				scanSteps = 0;
			}*/
		}
		
			//Update events
			update();

			//Draw this game
			drawGame();
	}
	
	
}





void MainGame::update() 
{

	if (robot.getX()* m_textureSize > m_screenWidth / 2)
	{
		offsetX = (robot.getX()* m_textureSize - m_screenWidth / 2);
	}
	else
	{
		offsetX = 0;
	}
	if (robot.getY()* m_textureSize > m_screenHeight / 2)
	{
		offsetY = (robot.getY()* m_textureSize - m_screenHeight / 2);
	}
	else
	{
		offsetY = 0;
	}
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;
	
	if (timer > delay)
	{
		timer = 0;
		if (robot.getRobotMode() == RobotMode::MANUAL)
		{
			robot.move();
		}
		else if (robot.getRobotMode() == RobotMode::SCAN)
		{
			robot.next_step();

			robot.move();
	
			robot.step();
		}
		else if (robot.getRobotMode() == RobotMode::AUTO)
		{
			if (robot.EmptyPath())
			{
				if (robot.exploreAppleData())
				{
					robot.algoritm();
				}
				else
				{
					robot.AutoEnd();
				}	
			}
			else
			{
				robot.move();	
			}
			 
		}
		if (sapper.getMode())
		{
			if (sapper.EmptyPath())
			{
				if (sapper.exploreMinesData())
				{
					sapper.algoritm();
				}
				else
				{
					sapper.AutoEnd();
				}
			}
			else
			{
				sapper.move();
			}
		}
		collision();
		checkBorderExploreData();

		s_robot.setPosition((robot.getX() * m_textureSize) - offsetX,panelSize + (robot.getY() * m_textureSize) - offsetY);
		if (sapper.getMode() == true)
		{
			s_sapper.setPosition((sapper.getX() * m_textureSize) - offsetX, panelSize + (sapper.getY() * m_textureSize) - offsetY);
		}
	}

	std::ostringstream Apple;
	Apple << numApples;
	text.setString("Apples: " + Apple.str() + "  Mode: " + robot.outRobotMode() + "  Sapper: " + sapper.outRobotMode());
}

void MainGame::scan()
{
	for (float i = -1; i <= 1; i += 1)
	{
		for (float j = -1; j <= 1; j += 1)
		{
			if ((i == -1 && j == 0) || (i == 0 && j == -1) || (i == 0 && j == 1) || (i == 1 && j == 0))
			{
				switch (m_levels[m_currentLevel]->getLevelData()[robot.getY() + i][robot.getX() + j])
				{
				case ' ':
					if((robot.getExploreData()[robot.getY() + i][robot.getX() + j] != ','))
					{
						robot.setExploreData(robot.getX() + j, robot.getY() + i, '.');
					}
					break;
				case '*':
					robot.setExploreData(robot.getX() + j, robot.getY() + i, '*');
					break;
				case 'B':
					robot.setExploreData(robot.getX() + j, robot.getY() + i, 'B');
					break;
				case '@':
					if ((robot.getExploreData()[robot.getY() + i][robot.getX() + j] != '$') )
					{
						robot.setExploreData(robot.getX() + j, robot.getY() + i, '@');
					}
					break;
				default:
					break;

				}
			}
		}
	}
	if (robot.getExploreData()[robot.getY()][robot.getX()] == ' ')
	{
		robot.setExploreData(robot.getX(), robot.getY(), '`');
	}
	else if (robot.getExploreData()[robot.getY()][robot.getX()] == '.')
	{
		robot.setExploreData(robot.getX(), robot.getY(), ',');
	}
	else if (robot.getExploreData()[robot.getY()][robot.getX()] == '@')
	{
		robot.setExploreData(robot.getX(), robot.getY(), '$');
	}
}


void MainGame::drawGame() 
{
	m_window.clear(Color::White);


	for (int i = 0; i < robot.getExploreDataHeight(); i++)
	{
		for (int j = 0; j < robot.getExploreDataWidht(); j++)
		{
			switch (robot.getExploreData()[i][j])
			{
			case ' ':
				s_map.setTextureRect(IntRect(16, 0, m_textureSize, m_textureSize));
				break;
			case '*':
				s_map.setTextureRect(IntRect(64, 0, m_textureSize, m_textureSize));
				break;
			case 'B':
				s_map.setTextureRect(IntRect(16, 0, m_textureSize, m_textureSize));
				break;
			case '.':
				s_map.setTextureRect(IntRect(0, 0, m_textureSize, m_textureSize));
				break;
			case ',':
				s_map.setTextureRect(IntRect(0, 0, m_textureSize, m_textureSize));
				break;
			case '`':
				/*robot.*/s_map.setTextureRect(IntRect(16, 0, m_textureSize, m_textureSize));
				break;
			case '@':
				/*robot.*/s_map.setTextureRect(IntRect(32, 0, m_textureSize, m_textureSize));
			case '$':
				/*robot.*/s_map.setTextureRect(IntRect(32, 0, m_textureSize, m_textureSize));
				break;
			default:
				throw "Unexpected symbol";
				break;
			}

			

			/*robot.*/s_map.setPosition(j * m_textureSize - offsetX, panelSize + i * m_textureSize - offsetY);

			m_window.draw(/*robot.*/s_map);

		}
	}

	m_window.draw(/*robot.*/s_robot);
	if(sapper.getMode() == true)
	{m_window.draw(/*robot.*/s_sapper); }
	
	m_window.draw(text);

	m_window.display();

}

void MainGame::collision()
{
	robot.setMode();
	sapper.setMode();

	if (robot.getExploreData()[robot.getY()][robot.getX()] == ' ')
	{
		robot.setExploreData(robot.getX(), robot.getY(), '`');
	}
	else if (robot.getExploreData()[robot.getY()][robot.getX()] == '.')
	{
		robot.setExploreData(robot.getX(), robot.getY(), ',');
	}
	else if (robot.getExploreData()[robot.getY()][robot.getX()] == '@')
	{
		robot.setExploreData(robot.getX(), robot.getY(), '$');
	}

	if (m_levels[m_currentLevel]->getLevelData()[robot.getY()][robot.getX()] == 'B' ||(robot.getX() == sapper.getX() && robot.getY() == sapper.getY() && sapper.getMode()))
	{

		robot.lastPosition();
	}

	if (robot.grab())
	{
		if (robot.getExploreData()[robot.getY()][robot.getX()] == '$')
		{ 
			robot.setExploreData(robot.getX(), robot.getY(), ',');
			m_levels[m_currentLevel]->takeApple(robot.getX(), robot.getY());
			numApples++;
		}

	}

	if (m_levels[m_currentLevel]->getLevelData()[robot.getY()][robot.getX()] == '*')
	{ 
		/*robot.*/s_robot.setPosition((robot.getX() * m_textureSize) - offsetX, panelSize + (robot.getY() * m_textureSize) - offsetY);
		text.setString("Game Over!");
		drawGame();

		Sleep(5000);
		m_window.close();
	}
		
		
	if (robot.scan())
	{
		scan();
	}
} // for robot and sapper


void MainGame::checkBorderExploreData()
{
	if (robot.getX() == robot.getExploreDataWidht() || (robot.scan() == true && robot.getX() == robot.getExploreDataWidht() - 1))
	{
		robot.resizeExploreData('R');
		collision();
	}
	if (robot.getY() == robot.getExploreDataHeight() - 1 || (robot.scan() == true && robot.getY() == robot.getExploreDataHeight() - 2))
	{
		robot.resizeExploreData('D');
		collision();
	}
	if (robot.getX() == 0 || (robot.scan() == true && robot.getX() == - 1))
	{
		robot.resizeExploreData('L');
		collision();
	}
	if (robot.getY() == 0 || (robot.scan() == true && robot.getY() == - 1))
	{
		robot.resizeExploreData('U');
		collision();
	}
} //only for robot

