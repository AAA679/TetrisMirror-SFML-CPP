#include <MenuState.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>
#include <SFML/Graphics/RenderWindow.hpp>


MenuState::MenuState(StateStack& stack, Context &context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::MenuBackground);
	mBackgroundSprite.setTexture(texture);
	
	auto newGameButton = std::make_shared<GUI::Button>(context);
	newGameButton->setPosition(300,380);
	newGameButton->setText("New Game");
	newGameButton->setCallback([this]()
		{
			requestStackPush(States::GameSettings);
		});

	auto LoadSavesButton = std::make_shared<GUI::Button>(context);
	LoadSavesButton->setPosition(300, 455);
	LoadSavesButton->setText("Load Saves");
	LoadSavesButton->setCallback([this]()
		{
			requestStackPush(States::LoadSave);
		});

	auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(300, 530);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this]()
		{			
			requestStackPush(States::KeySettings);
		});

	auto rankButton = std::make_shared<GUI::Button>(context);
	rankButton->setPosition(300, 605);
	rankButton->setText("Rank");
	rankButton->setCallback([this]()
		{
			requestStackPush(States::Rank);
		});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(300, 675);
	exitButton->setText("Back");
	exitButton->setCallback([this]()
		{
			requestStackPop();
			requestStackPush(States::Login);
		});

	mGUIContainer.pack(newGameButton);
	mGUIContainer.pack(LoadSavesButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(rankButton);
	mGUIContainer.pack(exitButton);

}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update()
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
		requestStackPush(States::Login);

	}

	return false;
}
