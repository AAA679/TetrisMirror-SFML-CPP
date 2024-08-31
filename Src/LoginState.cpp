#include <LoginState.h>
#include <TextField.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <SoundPlayer.h>
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


LoginState::LoginState(StateStack& stack, Context &context)
	: State(stack, context)
	, mGUIContainer()
	, mode(LoginState::Mode::Login)
{
	
	sf::Texture& texture = context.textures->get(Textures::MenuBackground);
	mBackgroundSprite.setTexture(texture);

	auto LogOrRegButton = std::make_shared<GUI::Button>(context);
	LogOrRegButton->setToggle(true);
	LogOrRegButton->setTexture(context.textures->get(Textures::Buttons));
	LogOrRegButton->setPosition(300, 400);
	LogOrRegButton->setText("Login Mode(click to change)",17);
	LogOrRegButton->setTextStyle(sf::Text::Italic);
	LogOrRegButton->setCallback([this, LogOrRegButton]()
		{	if (mode == 0) {
			LogOrRegButton->setText("Register Mode(click to change)", 17);
	} 
		else {
			LogOrRegButton->setText("Login Mode(click to change)", 17);
	}
			mode = (Mode)(!(bool)mode);
			LogOrRegButton->deactivate();
		});

	auto usernameField = std::make_shared<GUI::TextField>(context);
	usernameField->setTexture(context.textures->get(Textures::ID::Username));
	usernameField->setPosition(300, 475);
	usernameField->setTextPosition(53, 23);
	usernameField->setText("");
	
	auto passwordField = std::make_shared<GUI::TextField>(context);
	passwordField->setTexture(context.textures->get(Textures::ID::Password));
	passwordField->setPosition(300, 550);
	passwordField->setTextPosition(53, 23);
	passwordField->setText("");

	auto returnButton = std::make_shared<GUI::Button>(context);
	returnButton->setSpriteScale(0.5f, 1.f);
	returnButton->setPosition(450, 625);
	returnButton->setTextPosition(75,35.5f);
	returnButton->setText("Exit");
	returnButton->setCallback([this]()
		{
			requestStackPop();
		});

	auto enterButton = std::make_shared<GUI::Button>(context);
	enterButton->setSpriteScale(0.5f, 1.f);
	enterButton->setPosition(300, 625);
	enterButton->setTextPosition(75, 35.5f);
	enterButton->setText("Enter");
	enterButton->setCallback([this, &context]()
		{
			if (getMode() == LoginState::Mode::Register) {
					tryRegister(getUsernamePassword());
					context.mAccount->loginAccount(getUsernamePassword());
					
					requestStackPop();
					requestStackPush(States::Menu);				
			}
			else {
				switch (context.mAccount->loginAccount(getUsernamePassword()))
				{
				case Accounts::success:
					requestStackPop();
					requestStackPush(States::Menu);
					break;
				case Accounts::accountNotExist:
					std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(1))->changeTexture(GUI::TextField::Error);
					std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(1))->setText("");
					break;
				case Accounts::wrongPassword:
					std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(2))->changeTexture(GUI::TextField::Error);
					std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(2))->setText("");
					break;
				}
			}
			
		});
	mGUIContainer.pack(LogOrRegButton);
	mGUIContainer.pack(usernameField);
	mGUIContainer.pack(passwordField);
	mGUIContainer.pack(enterButton);
	mGUIContainer.pack(returnButton);
}

void LoginState::draw() {
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool LoginState::update() {
	return true;
}


bool LoginState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}

	return false;
}

LoginState::Mode LoginState::getMode() const{
	return mode;
};

std::pair<std::string, std::string>	LoginState::getUsernamePassword() {
	std::pair<std::string, std::string> res;
	res.first = std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(1))->getText();
	res.second = std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(2))->getText();
	processInputString(res.first);
	processInputString(res.second);
	return res;
}

void	LoginState::tryRegister(std::pair<std::string, std::string> UsernamePassword) {
	Accounts::Ptr tempPtr = (std::make_shared <Accounts>(UsernamePassword.first, UsernamePassword.second));
	tempPtr->registerAccount();
}
