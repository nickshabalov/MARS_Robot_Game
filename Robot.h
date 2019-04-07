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

	~Robot(); //����������
	
	void virtual move(); //���������

	void lastPosition(); // ��������� ������� (��� ������������ �� ������)

	bool grab(); // ����� �� ������  � �����

	bool scan(); //��������� �� �����

	void virtual setMode(); // ������� ����� ��� ������� �� ������

	//Sprite s_robot, s_map;

	int virtual getX() const { return x; } //������ ����������

	int virtual getY() const { return y; }

	int getExploreDataHeight() const { return m_exploreDataHeight; } //������ ������ �����

	int getExploreDataWidht() const { return m_exploreDataWidht; }

	std::vector < std::string > getExploreData() const {return m_exploreData;} //�������� ������ �����
	
	void setExploreData(int x, int y, char c); // ���������� �� �����  ����

	void resizeExploreData(char dir); //���������� ����� ������

	RobotMode getRobotMode() const; // ������ ����� ������

	std::string virtual outRobotMode() const; // ����� ������ ��� ������ �� ����

	void step(); // ������� ��� ��� ����������� ����� 

	void next_step(); // ������� �� ��������� ��� 

	void setNumSteps(int num_steps); //���������� ��������� ������

	bool virtual algoritm(); // ��������  ������ ���� � ������������ ���������� ��������
	
	bool exploreAppleData();// ����� ��������� �� �����

	void virtual AutoEnd(); //��������� ���������

	bool virtual EmptyPath(); // ��������� ����

private:

	int x, y; //���������� ������

	std::vector <std::string> m_exploreData; //����� ������

	int m_exploreDataHeight;//������ ����� ������

	int m_exploreDataWidht; 

	int lastX;//���������� ���� ����� ��� ������ ������������ �� ������

	int lastY; 

	RobotMode _mode; // ������� ����� ������ (������ ����� ������)

	int mode; // ������� ����� ���� (int ��� ������������)

	int numSteps; // ���������� ����� ��� ������������

	char dir; //����������� �������� ������ ��� ������������ ����� 

	std::vector < std::pair<int, int> > appleData; //���������� ���� ����� �� �����

	std::vector < std::pair<int, int> > path; //���� ��� ������ � ������ ����
};




