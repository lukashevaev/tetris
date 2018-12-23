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

	std::ifstream in("C:/Users/Екатерина Великая/source/repos/tetris/tetris/record.txt"); // окрываем файл для чтения
	if (in.is_open())//Пока файл in открыт в потоке для чтения
	{
		while (getline(in, line))//считываем файл построчно, хоть там и 1 число.
		{
			B = line;// B присваиваем строчке line из текста, хоть там и 1 число.
		}
	}
	in.close();     // закрываем файл

	std::stringstream A;//Переменная преобразовыватель из типа стр в тип инт.
	int C;
	A << B;
	A >> C;

	return C;
}
int RecordIn(int score)
{
	std::ofstream out;          // поток для записи
	out.open("C:/Users/Екатерина Великая/source/repos/tetris/tetris/record.txt"); // окрываем файл для записи с удалением предыдущего
	if (out.is_open())
	{
		out << score << std::endl;
	}
	return 0;
}