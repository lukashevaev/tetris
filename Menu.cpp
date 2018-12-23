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
		Event e;//КЛасс отвечающий за события на клавиатуре и не только
		while (window.pollEvent(e))//Пока не случилось какой либо действие ввиду нажатия клавиши
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Enter) game();
			    else if (e.key.code == Keyboard::Escape) return 0;
		}

		window.draw(s);//Представить рисунок , но не вывести на экран


		Font font;//шрифт 
		font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
		Text menutext("", font, 25);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		menutext.setFillColor(Color::Yellow);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		menutext.setString("Нажмите Enter чтобы начать игру \n \n или Esc чтобы выйти");
		menutext.setPosition(55, 200);
		window.draw(menutext);//рисую этот текст
		
		Text recordtext("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		recordtext.setFillColor(Color::Yellow);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		std::ostringstream record;    // объявили переменную
		record << maxscore;		//занесли в нее число очков, то есть формируем строку
		recordtext.setString("Игровой рекорд: " + record.str() + " очков.");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		recordtext.setPosition(210, 630);
		window.draw(recordtext);//рисую этот текст

		window.display();
	}	
}