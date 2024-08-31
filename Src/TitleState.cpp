#include <TitleState.h>
#include <Utility.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context& context)
	: State(stack, context)
	, mText()
	, displayIntro(false)
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("Press any key to start");
	mText.setCharacterSize(40);
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(1.5f);
	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(context.window->getSize() / 2u) + sf::Vector2f(0u, (context.window->getSize() / 3u).y));
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mTitle);
	if (mShowText)
		window.draw(mText);
}

bool TitleState::update()
{
	mTextEffectTime += sf::seconds(1.f / 60.f);

	if (mTextEffectTime >= sf::seconds(1.0f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		if (!displayIntro) {
			mBackgroundSprite.setTexture(getContext().textures->get(Textures::Intro));
			displayIntro = true;
			mText.move(0, 50);
			return true;
		}
		requestStackPop();
		requestStackPush(States::Login);
	}

	return true;
}