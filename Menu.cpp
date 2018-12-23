#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include "Game.h"
#include "Record.h"

using namespace sf;

int main()
{	
	RenderWindow window(VideoMode(500, 750), "Menu");

	Texture t;
	t.loadFromFile("images/tetris.jpg");

	Sprite s(t);

	int maxscore = 0;
	int scores = 0;

	while (window.isOpen())
	{
		maxscore = RecordOut();
		Event e;//����� ���������� �� ������� �� ���������� � �� ������
		while (window.pollEvent(e))//���� �� ��������� ����� ���� �������� ����� ������� �������
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Enter) game();
			    else if (e.key.code == Keyboard::Escape) return 0;
		}

		window.draw(s);//����������� ������� , �� �� ������� �� �����


		Font font;//����� 
		font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
		Text menutext("", font, 25);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		menutext.setFillColor(Color::Yellow);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
		menutext.setString("������� Enter ����� ������ ���� \n \n ��� Esc ����� �����");
		menutext.setPosition(55, 200);
		window.draw(menutext);//����� ���� �����
		
		Text recordtext("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		recordtext.setFillColor(Color::Yellow);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
		std::ostringstream record;    // �������� ����������
		record << maxscore;		//������� � ��� ����� �����, �� ���� ��������� ������
		recordtext.setString("������� ������: " + record.str() + " �����.");//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
		recordtext.setPosition(210, 630);
		window.draw(recordtext);//����� ���� �����

		window.display();
	}	
}