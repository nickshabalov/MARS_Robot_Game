#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<vector>
#include<functional>


using namespace sf;

enum class RobotMode { MANUAL, SCAN, AUTO };


class Robot
{
public:
	//Constructor 
	Robot();

	~Robot(); //деструктор
	
	void virtual move(); //двигаться

	void lastPosition(); // вернуться обратно (при столкновении со стеной)

	bool grab(); // берем ли яблоко  с карты

	bool scan(); //сканируем ли карту

	void virtual setMode(); // сменить режим при нажатии на кнопку

	//Sprite s_robot, s_map;

	int virtual getX() const { return x; } //узнать координаты

	int virtual getY() const { return y; }

	int getExploreDataHeight() const { return m_exploreDataHeight; } //узнать размер карты

	int getExploreDataWidht() const { return m_exploreDataWidht; }

	std::vector < std::string > getExploreData() const {return m_exploreData;} //передать данные карты
	
	void setExploreData(int x, int y, char c); // установить на карте  знак

	void resizeExploreData(char dir); //расширение карты робота

	RobotMode getRobotMode() const; // узнать режим робота

	std::string virtual outRobotMode() const; // режим робота для вывода на кран

	void step(); // сделать шаг при сканиовании карты 

	void next_step(); // взможен ли следующий шаг 

	void setNumSteps(int num_steps); //установить количетво шаговв

	bool virtual algoritm(); // алгоритм  поиска пути и сотставление кратчашего маршрута
	
	bool exploreAppleData();// найти всеяблоки на карте

	void virtual AutoEnd(); //завешрить авторежим

	bool virtual EmptyPath(); // проверить путь

private:

	int x, y; //координаты робота

	std::vector <std::string> m_exploreData; //карта робота

	int m_exploreDataHeight;//размер карты робота

	int m_exploreDataWidht; 

	int lastX;//предыдущие шаги рбота для случая столкновения со стеной

	int lastY; 

	RobotMode _mode; // Текущий режим робота (вообще можно убрать)

	int mode; // текуший режим роба (int для зацикливания)

	int numSteps; // количество шагов при сканировании

	char dir; //направление движения робота для сканирования карты 

	std::vector < std::pair<int, int> > appleData; //Координаты всех яблок на карте

	std::vector < std::pair<int, int> > path; //Путь для робота в режиме авто
};




