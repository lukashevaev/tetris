#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
int RecordOut()
{
	std::string line;
	std::string B;

	std::ifstream in("C:/Users/��������� �������/source/repos/tetris/tetris/record.txt"); // �������� ���� ��� ������
	if (in.is_open())//���� ���� in ������ � ������ ��� ������
	{
		while (getline(in, line))//��������� ���� ���������, ���� ��� � 1 �����.
		{
			B = line;// B ����������� ������� line �� ������, ���� ��� � 1 �����.
		}
	}
	in.close();     // ��������� ����

	std::stringstream A;//���������� ����������������� �� ���� ��� � ��� ���.
	int C;
	A << B;
	A >> C;

	return C;
}
int RecordIn(int score)
{
	std::ofstream out;          // ����� ��� ������
	out.open("C:/Users/��������� �������/source/repos/tetris/tetris/record.txt"); // �������� ���� ��� ������ � ��������� �����������
	if (out.is_open())
	{
		out << score << std::endl;
	}
	return 0;
}