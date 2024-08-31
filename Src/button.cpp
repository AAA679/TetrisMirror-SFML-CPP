#include <Button.h>
#include <Utility.h>
#include <SoundPlayer.h>
#include <ResourceHolder.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Button::Button(State::Context context)
		: mCallback()
		, mSprite(context.textures->get(Textures::Buttons))
		, mInputFont(context.fonts->get(Fonts::Input))
		, mText("", context.fonts->get(Fonts::Main), 16)
		, mIsToggle(false)
		, mSounds(*context.sounds)
	{
		changeTexture(Normal);
		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::setText(const std::string& text)
	{
		mText.setString(text);
		setTextColor(sf::Color::White);
		mText.setOutlineColor(sf::Color::Black);
		mText.setOutlineThickness(2.4f);
		mText.setCharacterSize(35);
		centerOrigin(mText);

	}

	void Button::setText(const std::string& text,const unsigned int size)
	{	
		mText.setString(text);
		setTextColor(sf::Color::White);
		mText.setOutlineColor(sf::Color::Black);
		mText.setOutlineThickness(2.4f);
		mText.setCharacterSize(size);
		centerOrigin(mText);
	}

	void  Button::changeFont() {
		mText.setFont(mInputFont);
		return;
	}


	void Button::setToggle(bool flag)
	{
		mIsToggle = flag;
	}

	void Button::setTexture(sf::Texture& texture) {
		mSprite.setTexture(texture);
	}

	void Button::setTextColor(sf::Color color) {
		mText.setFillColor(color);
	}


	void Button::setTextStyle(sf::Text::Style style) {
		mText.setStyle(style);
	}
	void Button::setTextPosition(float x, float y) {
		mText.setPosition(x,y);
	}

	void Button::setSpriteScale(float x, float y) {
		mSprite.setScale(x, y);
	}

	bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();
		mSounds.play(SoundEffect::Button);
		changeTexture(Selected);
	}

	void Button::deselect()
	{
		Component::deselect();

		changeTexture(Normal);
	}

	void Button::activate()
	{
		Component::activate();


		// If we are toggle then we should show that the button is pressed and thus "toggled".
		if (mIsToggle) {
			changeTexture(Pressed);
		}

		if (mCallback)
			mCallback();

		// If we are not a toggle then deactivate the button since we are just momentarily activated.
		if (!mIsToggle)
			deactivate();

		mSounds.play(SoundEffect::Button);
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if (mIsToggle)
		{
			// Reset texture to right one depending on if we are selected or not.
			if (isSelected())
				changeTexture(Selected);
			else
				changeTexture(Normal);
		}
	}

	void Button::handleEvent(const sf::Event&)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

	void Button::changeTexture(Type buttonType)
	{
		sf::IntRect textureRect(0, 71 * buttonType, 300, 71);
		mSprite.setTextureRect(textureRect);
	}

}
