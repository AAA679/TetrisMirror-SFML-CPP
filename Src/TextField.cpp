#include <TextField.h>


#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace GUI;

TextField::TextField(State::Context context) :
	maxLength(20ull),
	mSprite(context.textures->get(Textures::Buttons)),
	mText("", context.fonts->get(Fonts::Input), 10),
	mSounds(*context.sounds)
{
	changeTexture(Normal);

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);

}


bool TextField::isSelectable() const
{
	return true;
}

void TextField::setText(const std::string& text)
{
	mText.setString(text);
	mText.setFillColor(sf::Color::Black);
	mText.setCharacterSize(20);
	centerOrigin(mText);
}

std::string TextField::getText() const{
	std::string s=mText.getString();
	return s;
}

void TextField::setTextPosition(float x, float y) {
	mText.setPosition(x, y);
}

void TextField::setTexture(sf::Texture& texture) {
	mSprite.setTexture(texture);
}

void TextField::select()
{
	Component::select();
	mSounds.play(SoundEffect::Button);
	changeTexture(Selected);
}

void TextField::deselect()
{
	Component::deselect();

	changeTexture(Normal);
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void TextField::changeTexture(Type fieldType)
{
	sf::IntRect textureRect(0, 71 * fieldType, 300, 71);
	mSprite.setTextureRect(textureRect);
}

void  TextField::setSpriteScale(float x, float y) {
	mSprite.setScale(x, y);
}

void TextField::handleEvent(const sf::Event& event)
{	
	if (event.key.code == sf::Keyboard::Enter&& event.type == sf::Event::KeyReleased) {
		deactivate();
		return;
	}
	if (event.type != sf::Event::TextEntered||!isActive())
		return;
	if (event.text.unicode == 27) {
		deactivate();
		return;
	}
	std::string tempString = getText();

	if (event.text.unicode == 8) {   // Delete key
		mText.setString(tempString.substr(0, tempString.size() - 1));
	}
	else if (tempString.size() < maxLength) {//Enter key
		tempString += event.text.unicode;
		mText.setString(tempString);
	}

}