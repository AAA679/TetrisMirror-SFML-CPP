#pragma once
#include <State.h>
#include <CommandQueue.h>
#include <Utility.h>
#include <Saves.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class GameState : public State
{
public:
										GameState(StateStack& stack, Context &context);

	virtual void						draw();
	virtual bool						update();
	virtual bool						handleEvent(const sf::Event& event);

	void								blockmove(sf::Vector2u move);
	void								spin();
	void								dropBotton();
	void								drop();
	void								pushMagicState();

private:

	void								clean();
	bool								checkFail() const;
	void								updateSounds();
	bool								checkblock(sf::Vector2u blockPos[4]) const;
	void								newblock();

	void								copyData();

private:
	CommandQueue						mCommandQueue;
	sf::Sprite							mBlockSprite;
	sf::Sprite							mTableSprite;
	sf::Sprite							mGUISprite;
	sf::Sprite							mMagicSprite;
	sf::Sprite							mNextBlockSprite;

	sf::Text							mCurrentScoreText;
	sf::Text							mBestScoreText;
	sf::Text							mCurrentScoreNumText;
	sf::Text							mBestScoreNumText;
	sf::Text							mMagicText;
	sf::Text							mMagicNumText;
	sf::Text							mComboText;

	SoundPlayer&						mSound;

	Saves::Ptr							mSave;
	unsigned int						width;
	unsigned int						height;
	unsigned int						speed;
	unsigned int						magic;
	unsigned int						gamegrade;
	const unsigned int					blockSize=30;
	const unsigned int					margin=20;
	sf::Time							blockGenerateInterval;
	bool								useMagic;
	bool								initNextBlockID;
	bool								comboDispaly;


	size_t								currentScore;
	Blocks::ID							currentBlockID;
	Blocks::ID							nextBlockID;
	sf::Vector2u						currentBlockPos[4];
	sf::Vector2u						beforeBlockPos[4];

	std::vector<std::vector<Blocks::ID>>mTable;//Current block table

	sf::Clock							gameClock;
	sf::Time							blockTimer;
	sf::Clock							comboClock;
	sf::Time							comboTimer;
};
