#pragma once
#include <ResourceIdentifiers.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <sstream>
#include <direct.h>  // 包含用于创建文件夹的函数

bool createDirectory(const std::string& path);

namespace sf
{
	class Sprite;
	class Text;
}

class Animation;

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string		toString(const T& value);

// Convert enumerators to strings
std::string		toString(sf::Keyboard::Key key);


//Convert enumerators to strings
std::string		toString(Music::ID id);


// Convert strings to enumerators
sf::Keyboard::Key toKey(std::string key);

// Convert string to int
size_t	toInt(std::string s);

// Call setOrigin() with the center of the object
void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);
//void			centerOrigin(Animation& animation);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);


void			processInputString(std::string& s);

unsigned int long long hashString(std::string);

template <typename T>
std::string toString(const T& value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}
