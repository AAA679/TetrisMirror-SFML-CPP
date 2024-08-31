#include <GameSettingsState.h>
#include <Button.h>
#include <Utility.h>
#include <ResourceHolder.h>
#include <textField.h>
#include <Saves.h>

#include <SFML/Graphics/RenderWindow.hpp>


GameSettingsState::GameSettingsState(StateStack& stack, Context &context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::MenuBackground);
	mBackgroundSprite.setTexture(texture);

	auto widthField = std::make_shared<GUI::TextField>(context);
	widthField->setTexture(context.textures->get(Textures::ID::Width));
	widthField->setPosition(300, 400);
	widthField->setTextPosition(100, 34);
	widthField->setText("10");

	auto heightField = std::make_shared<GUI::TextField>(context);
	heightField->setTexture(context.textures->get(Textures::ID::Height));
	heightField->setPosition(300, 475);
	heightField->setTextPosition(100, 34);
	heightField->setText("20");

	auto speedField = std::make_shared<GUI::TextField>(context);
	speedField->setTexture(context.textures->get(Textures::ID::Speed));
	speedField->setPosition(300, 550);
	speedField->setTextPosition(100, 34);
	speedField->setText("1");

	
	auto enterButton = std::make_shared<GUI::Button>(context);
	enterButton->setSpriteScale(0.5f, 1.f);
	enterButton->setPosition(300, 625);
	enterButton->setTextPosition(75, 35.5f);
	enterButton->setText("Enter");
	enterButton->setCallback([this,&context]()
		{
			auto tp = GameSettingsState::getSettings();
			context.mSave->setWidth(tp.first.first);
			context.mSave->setHeight(tp.first.second);
			context.mSave->setSpeed(tp.second);
			context.mSave->resetTable();

			requestStateClear();
			requestStackPush(States::Game);
		});


	auto returnButton = std::make_shared<GUI::Button>(context);
	returnButton->setSpriteScale(0.5f, 1.f);
	returnButton->setPosition(450, 625);
	returnButton->setTextPosition(75, 35.5f);
	returnButton->setText("Exit");
	returnButton->setCallback([this]()
		{
			requestStackPop();
		});


	mGUIContainer.pack(widthField);
	mGUIContainer.pack(heightField);
	mGUIContainer.pack(speedField);
	mGUIContainer.pack(enterButton);
	mGUIContainer.pack(returnButton);

}

std::pair<std::pair<unsigned int, unsigned int>, unsigned int>	GameSettingsState::getSettings() {
	std::pair<std::pair<unsigned int, unsigned int>, unsigned int> res;
	std::string tp;
	tp = std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(0))->getText();
	processInputString(tp);
	res.first.first = toInt(tp);

	tp = std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(1))->getText();
	processInputString(tp);
	res.first.second = toInt(tp);

	tp = std::dynamic_pointer_cast<GUI::TextField>(mGUIContainer.getChild(2))->getText();
	processInputString(tp);
	res.second = toInt(tp);

	return res;
}

void GameSettingsState::draw() {
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool GameSettingsState::update() {
	return true;
}

bool  GameSettingsState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}
	return false;
}
