#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include "Record.h"

using namespace sf;

const int M = 13;
const int N = 10;
int score = 0;

int field[M][N] = { 0 };//������� ���� ��������

struct Point
{
	int x, y;
}
a[4], b[4];
int figures[7][4] =
{
	1,3,5,7,//I
	2,4,5,7,//Z
	3,5,4,6,//S
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//O

};//������� ��� ������� �� �����������

bool check()//�������� ��������� ����������� ������
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
}
int game()
{	
	RenderWindow window(VideoMode(500, 750), "The game!");


	Texture t;
	t.loadFromFile("images/tetris.jpg");

	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, 50, 50));

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())
	{
		/*Texture f;
		f.loadFromFile("images/Fon.jpg");
		Sprite q(f);
		window.draw(q);*/

		float time = clock.getElapsedTime().asSeconds();//�������� � ���������
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		//////// <-Move-> ///////
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

		///// <-Rotate-> /////
		if (rotate)
		{
			Point p = a[1];//����� ��������
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		}

		///////Tick////////
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

			if (!check())
			{
				for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

				colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer = 0;
		}

		////////check lines/////////
		int k = M - 1;
		int count = 0;
		for (int i = M - 1; i > 0; i--)
		{
			count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];//��������������� ������ , ������� ������ ����� �������
			}
			if (count < N) k--;//���� ������� ������� N �� ��������� ��������� count �� ��������� �� ������� �������.
			else if (count == N) score++;
		}

		k = 1;
		count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[k][j]) count++;//������� ���� �� ����������� ����� �� ������� �������
		}
		if (count > 0)//���� ���� ���� ���� ������� ������� �� �����������
		{
			t.loadFromFile("images/lose.jpg");
			Sprite s(t);
			window.draw(s);
			window.display();
			Sleep(2000);
			int rec = RecordOut();
			if (score>rec) RecordIn(score);//���� ����� � ����� ������ ��� �� ������ ������� �� ������� � ����
			for (int i = M - 1; i > 0; i--)
			{				
				for (int j = 0; j < N; j++)
				{					
					field[i][j] = 0;//������� ����
				}
			}
			score = 0;
			return 0;
		}

		int n = 3;
		if (a[0].x == 1000)
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}

		dx = 0; rotate = 0; delay = 0.3;

		///////draw/////////
		window.clear(Color::Magenta);

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				s.setTextureRect(IntRect(field[i][j] * 50, 0, 50, 50));
				s.setPosition(j * 50, i * 50);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++) {
			s.setTextureRect(IntRect(colorNum * 50, 0, 50, 50));
			s.setPosition(a[i].x * 50, a[i].y * 50);
			window.draw(s);
		}
		window.draw(s);


		//////////Scores////////////

		Font font;//����� 
		font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
		Text scoretext("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		scoretext.setFillColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
		scoretext.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

		

		std::ostringstream playerScoreString;    // �������� ����������
		playerScoreString << score;		//������� � ��� ����� �����, �� ���� ��������� ������
		scoretext.setString("����:" + playerScoreString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
		scoretext.setPosition(400, 0);
		window.draw(scoretext);//����� ���� �����

		


		window.display();
	}

	return 0;
}