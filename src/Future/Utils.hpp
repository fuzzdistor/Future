#ifndef UTILS_HPP
#define UTILS_HPP

#include "Future/json.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

using json = nlohmann::json;

namespace sf
{
    class Sprite;
    class Text;
}

class SpriteNode;

namespace util
{

// Convert enumerators to strings
std::string        toString(sf::Keyboard::Key key);

json            readDataFromFile(std::string filePath);

void            centerOrigin(SpriteNode& spriteNode);
void            centerOrigin(sf::Sprite& sprite);
void            centerOrigin(sf::Text& text);

float            toDegree(float radian);
float            toRadian(float degree);

// Random number generation

int                randomInt(int exclusiveMax);

// Vector operations

float            length(sf::Vector2f vector);
sf::Vector2f    unitVector(sf::Vector2f vector);

}

#endif // UTILS_HPP
