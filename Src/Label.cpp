#include <Label.h>
#include <Utility.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Label::Label(const std::string& text, const FontHolder& fonts)
		: mText(text, fonts.get(Fonts::Main), 16)
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event&)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::setText(const std::string& text,const size_t size)
	{
		mText.setString(text);
		//mText.setColor(sf::Color::Black);
		mText.setOutlineColor(sf::Color::Black);
		mText.setOutlineThickness(1.f);
		mText.setCharacterSize(size);
	}

}