#pragma once
#include <State.h>
#include <Container.h>
#include <Button.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class SaveGameState : public State
{
public:
							SaveGameState(StateStack& stack, Context& context);

	virtual void			draw();
	virtual bool			update();
	virtual bool			handleEvent(const sf::Event& event);

	void					addSaveLabel(const Context &context,size_t saveID, float y, const std::string& time , std::string& score, std::string& width, std::string& height, std::string& speed);
	void					saveGame(size_t saveID);

private:
	void					scanSaves();

private:
	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;
};
