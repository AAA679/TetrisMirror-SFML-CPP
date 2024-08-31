#pragma once
#include <State.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
public:
						TitleState(StateStack& stack, Context &context);

	virtual void		draw();
	virtual bool		update();
	virtual bool		handleEvent(const sf::Event& event);


private:
	bool				displayIntro;
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText,mTitle;
	bool				mShowText;
	sf::Time			mTextEffectTime;
};
