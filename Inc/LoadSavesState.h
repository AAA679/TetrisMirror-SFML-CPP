#pragma once
#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LoadSavesState : public State
{
public:
	LoadSavesState(StateStack& stack, Context& context);

	virtual void			draw();
	virtual bool			update();
	virtual bool			handleEvent(const sf::Event& event);

	void					addSaveLabel(const Context& context, size_t saveID, float y, const std::string& time, std::string& score, std::string& width, std::string& height, std::string& speed);
	void					loadSave(size_t SaveID);
private:
	void					scanSaves();
	void					deleteSave();
private:
	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;
};

