#pragma once
// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		TitleScreen,
		BlocksSkin,
		BaseButtons,
		Buttons,
		Rank,
		Save,
		Particle,
		Intro,
		MenuBackground,
		GameTableBackground,
		RankBackground,
		MagicBackground,
		MagicBlock,
		GameNextBlockBackground,
		GameGUIBackground,
		SettingBackground,
		GameoverBackground,
		PauseBackground,
		LeftArrow,
		RightArrow,
		Username,
		Password,
		Width,
		Height,
		Speed,
	};
}

namespace Image
{
	enum ID
	{
		Icon,
	};
}

namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Input,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Button,
		Back,
		Drop,
		LineClear,
		Combo,
	};
}

namespace Music
{
	enum ID
	{
		MirrorOfEdge,
		TrackInTime,
		Distance,
	};
}



namespace Blocks
{
	const int blocks[7][4] =
	{ {2,4,6,7},//OrangeRicky
		{3,5,7,6},//BlueRicky
		{2,4,5,7},//ClevelandZ
		{3,5,4,6},//RhodeIslandZ
		{1,3,5,7},//Hero
		{3,5,4,7},//Teewee
		{2,3,4,5} //Smashboy
	};
	enum ID
	{
		None,
		OrangeRicky,
		BlueRicky,
		ClevelandZ,
		RhodeIslandZ,
		Hero,
		Teewee,
		Smashboy,
	};

};

#include <SFML/Graphics.hpp>

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;
typedef ResourceHolder<sf::Image,Image::ID>					ImageHolder;
