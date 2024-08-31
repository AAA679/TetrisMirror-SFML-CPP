#pragma once
#include <fstream>
#include <State.h>
#include <Container.h>
#include <StateStack.h>
#include <Accounts.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LoginState :public State
{
public:
	
	enum Mode
	{
		Login,
		Register
	};

public:
										LoginState(StateStack& stack, Context &context);
	virtual void						draw();
	virtual bool						update();
	virtual bool						handleEvent(const sf::Event& event);
	Mode								getMode()const;
	std::pair<std::string, std::string>	getUsernamePassword();
	void								tryRegister(std::pair<std::string, std::string> UsernamePassword);

private:
	sf::Sprite							mBackgroundSprite;
	GUI::Container						mGUIContainer;
	Mode								mode;
};
