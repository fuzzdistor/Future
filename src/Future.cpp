// Future.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Main Window");

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(80.f);

	sf::Font font;
	font.loadFromFile("../media/JetBrainsMono.otf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20U);
	text.setString("Hey");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}

		window.clear();
		window.draw(circle);
		window.draw(text);
		window.display();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
