#include <Application.h>
#include <Utility.h>
#include <State.h>
#include <StateIdentifiers.h>
#include <MusicPlayer.h>

#include <TitleState.h>
#include <LoginState.h>
#include <GameState.h>
#include <MenuState.h>
#include <StateStack.h>
#include <SaveGameState.h>
#include <LoadSavesState.h>
#include <PauseState.h>
#include <RankState.h>
#include <MagicState.h>
#include <KeySettingState.h>
#include <GameSettingsState.h>
#include <GameoverState.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(909, 909), "TetrisMirror", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mMusic()
	, mSounds()
	, mImage()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mMusic, mSounds,mImage))
{
	//load resourses
	mImage.load(Image::Icon, "Media/Textures/icon.png");

	mFonts.load(Fonts::Main, "Media/Font/Qualy Bold.ttf");
	mFonts.load(Fonts::Input, "Media/Font/Sansation.ttf");

	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	mTextures.load(Textures::BaseButtons, "Media/Textures/BaseButtons.png");
	mTextures.load(Textures::Buttons, "Media/Textures/Buttons.png");
	mTextures.load(Textures::Rank, "Media/Textures/Rank.png");
	mTextures.load(Textures::Save, "Media/Textures/SaveButtons.png");
	mTextures.load(Textures::Intro, "Media/Textures/Intro.png");
	mTextures.load(Textures::MenuBackground, "Media/Textures/MenuBackground.png");
	mTextures.load(Textures::SettingBackground, "Media/Textures/settingBackground.png");
	mTextures.load(Textures::GameoverBackground, "Media/Textures/gameoverBackground.png");
	mTextures.load(Textures::MagicBackground, "Media/Textures/MagicBackground.png");
	mTextures.load(Textures::PauseBackground, "Media/Textures/pauseBackground.png");
	mTextures.load(Textures::RankBackground, "Media/Textures/rankBackground.png");
	mTextures.load(Textures::Username, "Media/Textures/usernameField.png");
	mTextures.load(Textures::Password, "Media/Textures/passwordField.png");
	mTextures.load(Textures::Width, "Media/Textures/widthField.png");
	mTextures.load(Textures::Height, "Media/Textures/heightField.png");
	mTextures.load(Textures::Speed, "Media/Textures/speedField.png");
	mTextures.load(Textures::BlocksSkin, "Media/Textures/BlocksSkin0.png");
	mTextures.load(Textures::MagicBlock, "Media/Textures/MagicBlock.png");
	mTextures.load(Textures::LeftArrow, "Media/Textures/LeftArrow.png");
	mTextures.load(Textures::RightArrow, "Media/Textures/RightArrow.png");
	mTextures.load(Textures::GameTableBackground, "Media/Textures/gameTableBackground.png");
	mTextures.load(Textures::GameGUIBackground, "Media/Textures/gameGUIBackground.png");
	mTextures.load(Textures::GameNextBlockBackground, "Media/Textures/gameNextBlockBackground.png");

	//initial window
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
	sf::Image icon = mImage.get(Image::Icon);
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//registerStaes in Factories
	registerStates();
	mStateStack.pushState(States::Title);

	//Initial Music
	mMusic.setVolume(40.f);
	mMusic.play(Music::MirrorOfEdge);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update();

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update()
{
	mStateStack.update();
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}


void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<LoginState>(States::Login);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<RankState>(States::Rank);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<MagicState>(States::Magic);
	mStateStack.registerState<SaveGameState>(States::SaveGame);
	mStateStack.registerState<LoadSavesState>(States::LoadSave);
	mStateStack.registerState<KeySettingsState>(States::KeySettings);
	mStateStack.registerState<GameSettingsState>(States::GameSettings);
	mStateStack.registerState<GameoverState>(States::GameOver);
}
