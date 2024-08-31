#pragma once
#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>


class MagicState : public State
{
public:
						MagicState(StateStack& stack, Context& context);

	virtual void		draw();
	virtual bool		update();
	virtual bool		handleEvent(const sf::Event& event);


private:
	size_t				blockNum;
	sf::RectangleShape	glassBackground;
	sf::Sprite			mBackgroundSprite;
	sf::Sprite			mBlockSprite;
	GUI::Container		mGUIContainer;
};
