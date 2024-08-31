#pragma once
#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>


class PauseState : public State
{
public:
						PauseState(StateStack& stack, Context& context);

	virtual void		draw();
	virtual bool		update();
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Text			mText;
	sf::Text			mScore;
	sf::RectangleShape	glassBackground;
	sf::Sprite			mBackgroundSprite;
	GUI::Container		mGUIContainer;
};
