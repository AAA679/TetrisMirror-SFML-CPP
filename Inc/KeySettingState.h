#pragma once

#include <State.h>
#include <Accounts.h>
#include <Container.h>
#include <Button.h>
#include <Label.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class KeySettingsState : public State
{
public:
									KeySettingsState(StateStack& stack, Context &context);

	virtual void					draw();
	virtual bool					update();
	virtual bool					handleEvent(const sf::Event& event);


private:
	void							updateLabels();
	void							addButtonLabel(Accounts::ActionID action, float y, const std::string& text, Context context);


private:
	sf::Sprite												mBackgroundSprite;
	sf::Sprite												mBlockSprite;
	GUI::Container											mGUIContainer;
	std::array<GUI::Button::Ptr, Accounts::ActionCount>		mBindingButtons;
	std::array<GUI::Label::Ptr, Accounts::ActionCount>		mBindingLabels;
};


