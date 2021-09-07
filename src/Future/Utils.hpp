#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

namespace sf
{
	class Sprite;
	class Text;
}


namespace util
{

// Convert enumerators to strings

std::string		toString(sf::Keyboard::Key key);

void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation

int				randomInt(int exclusiveMax);

// Vector operations

float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

}

#endif // UTILS_HPP
