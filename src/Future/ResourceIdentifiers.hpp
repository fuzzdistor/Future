#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Future/json.hpp"

namespace sf
{
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum class ID
	{
        House,
		BlueGuy,
		RedGuy,
		Enemy,
		Wall,
		Door,
		Background,
		TitleScreen,
		GUITitleScreen,
		GUIButtonNormal,
		GUIButtonSelected,
		GUIButtonPressed,
		INVALID,
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(Textures::ID, {
		{Textures::ID::INVALID, nullptr},
		{Textures::ID::House, "House"},
		{Textures::ID::BlueGuy, "BlueGuy"},
		{Textures::ID::RedGuy, "BlueGuy"},
		{Textures::ID::Enemy, "Enemy"},
		{Textures::ID::Wall, "Wall"},
		{Textures::ID::Door, "Door"},
		{Textures::ID::Background, "Background"},
		{Textures::ID::TitleScreen, "TitleScreen"},
		{Textures::ID::GUITitleScreen, "GUITitleScreen"},
		{Textures::ID::GUIButtonNormal, "GUIButtonNormal"},
		{Textures::ID::GUIButtonSelected, "GUIButtonSelected"},
		{Textures::ID::GUIButtonPressed, "GUIButtonPressed"},
	})
}

namespace Fonts
{
	enum class ID
	{
		Main,
		Mono,
		INVALID,
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(Fonts::ID, {
		{Fonts::ID::INVALID, nullptr},
		{Fonts::ID::Main, "Main"},
		{Fonts::ID::Mono, "Mono"},
	})
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP