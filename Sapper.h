#include "Robot.h"
#pragma once
class Sapper : public Robot
{
public:
	Sapper();

	~Sapper();
	
	void virtual move(); //���������

	bool getMode() const { return SapperMode; }

	int virtual getX() const { return x; } //������ ����������

	int virtual getY() const { return y; }

	std::string virtual outRobotMode() const; // ����� ������ ��� ������ �� ����

	void virtual setMode(); // ������� ����� ��� ������� �� ������

	bool virtual algoritm(); // ��������  ������ ���� � ������������ ���������� ��������

	bool exploreMinesData();// ����� ��� ���� �� �����


	void virtual AutoEnd(); //��������� ���������

	bool virtual EmptyPath(); // ��������� ����

private:

	int x, y;

	int lastX;//���������� ���� ����� ��� ������ ������������ �� ������

	int lastY;

	bool SapperMode;

	std::vector <std::pair<int, int> > minesData;

	std::vector < std::pair<int, int> > path; //���� ��� ������ � ������ ����
};




	
