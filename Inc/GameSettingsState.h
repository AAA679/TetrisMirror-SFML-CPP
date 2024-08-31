#pragma once
#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameSettingsState : public State
{
public:
	GameSettingsState(StateStack& stack, Context &context);

	virtual void			draw();
	virtual bool			update();
	virtual bool			handleEvent(const sf::Event& event);

	std::pair<std::pair<unsigned int,unsigned int>, unsigned int>	getSettings();

private:

	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;
};
