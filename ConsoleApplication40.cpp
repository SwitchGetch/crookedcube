#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;
using namespace chrono;

class Player
{
	sf::RectangleShape rectangle;

	float jump_arg = 4;

	int side;

	float cordX;
	float cordY;

	int minX = 0;
	int minY = 0;
	int maxX;
	int maxY;

	int red;
	int green;
	int blue;

	int randomValue(int lower, int upper)
	{
		return lower + rand() % (upper - lower + 1);
	}

public:

	Player(int winX, int winY)
	{
		this->side = min(winX, winY) / 4;

		this->maxX = winX - this->side;
		this->maxY = winY - this->side;

		this->cordX = this->maxX / 2;
		this->cordY = this->maxY / 2;

		rectangle.setSize(sf::Vector2f(this->side, this->side));
		rectangle.setPosition(sf::Vector2f(this->cordX, this->cordY));
	}

	void jump()
	{
		this->jump_arg = 0;
	}

	void move()
	{
		this->cordY += (this->jump_arg * (this->jump_arg - 4));

		this->jump_arg += 0.1;

		this->rectangle.setPosition(sf::Vector2f(this->cordX, this->cordY));
	}

	void setRandomColor()
	{
		this->red = randomValue(0, 255);
		this->green = randomValue(0, 255);
		this->blue = randomValue(0, 255);

		rectangle.setFillColor(sf::Color(this->red, this->green, this->blue));
	}

	sf::RectangleShape getShape()
	{
		return this->rectangle;
	}
};

int main()
{
	srand(time(NULL));

	int winX, winY;

	cout << "window size: ";
	cin >> winX >> winY;

	Player player(winX, winY);

	player.setRandomColor();

	sf::RenderWindow window(sf::VideoMode(winX, winY), "My window");


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.scancode == sf::Keyboard::Scan::Space)
				{
					player.jump();
				}
			}
		}

		window.clear(sf::Color::Black);

		window.draw(player.getShape());

		window.display();

		player.move();

		this_thread::sleep_for(milliseconds(1));
	}
}