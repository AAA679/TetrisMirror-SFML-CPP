#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <State.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <StateStack.h>
class Application {
public:
							Application();
	void					run();

private:
	void					processInput();
	void					update();
	void					render();
	void					registerStates();

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	ImageHolder				mImage;
	MusicPlayer				mMusic;
	SoundPlayer				mSounds;
	StateStack				mStateStack;
};