#include "Robot.h"
#pragma once
class Sapper : public Robot
{
public:
	Sapper();

	~Sapper();
	
	void virtual move(); //двигаться

	bool getMode() const { return SapperMode; }

	int virtual getX() const { return x; } //узнать координаты

	int virtual getY() const { return y; }

	std::string virtual outRobotMode() const; // режим робота для вывода на кран

	void virtual setMode(); // сменить режим при нажатии на кнопку

	bool virtual algoritm(); // алгоритм  поиска пути и сотставление кратчашего маршрута

	bool exploreMinesData();// найти все мины на карте


	void virtual AutoEnd(); //завешрить авторежим

	bool virtual EmptyPath(); // проверить путь

private:

	int x, y;

	int lastX;//предыдущие шаги рбота для случая столкновения со стеной

	int lastY;

	bool SapperMode;

	std::vector <std::pair<int, int> > minesData;

	std::vector < std::pair<int, int> > path; //Путь для робота в режиме авто
};




	
