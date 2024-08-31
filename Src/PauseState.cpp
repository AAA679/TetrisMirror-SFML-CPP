#include <PauseState.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>
#include <SFML/Graphics/RenderWindow.hpp>


PauseState::PauseState(StateStack& stack, Context& context)
	: State(stack, context)
	, mText("", context.fonts->get(Fonts::Main), 25)
	, mScore("", context.fonts->get(Fonts::Main), 25)
	, mGUIContainer()
{

	//calculate rational transform 
	sf::Vector2u windowSize = context.window->getSize();
	unsigned int length = std::min(windowSize.x, windowSize.y) / 3.f * 2.f;
	sf::Vector2f scaleRatio;
	scaleRatio.x = scaleRatio.y = float(length) / 300.f;

	//set frosted glass background
	glassBackground.setSize(sf::Vector2f(context.window->getSize().x, context.window->getSize().y));
	glassBackground.setFillColor(sf::Color(0, 0, 0, 128));


	sf::Texture& texture = context.textures->get(Textures::PauseBackground);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setPosition((windowSize.x - length) / 2.f, (windowSize.y - length) / 2.f);
	mBackgroundSprite.setScale(scaleRatio);

	auto continueGameButton = std::make_shared<GUI::Button>(context);
	continueGameButton->setPosition(windowSize.x / 2.f - 150 * scaleRatio.x * 0.8, windowSize.y / 2.f + length / 5.f - 2*71.f * scaleRatio.y * 0.8);
	continueGameButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	continueGameButton->setText("Continue Game",30);
	continueGameButton->setCallback([this, &context]()
		{
			requestStackPop();
		});

	auto saveGameButton = std::make_shared<GUI::Button>(context);
	saveGameButton->setPosition(windowSize.x / 2.f - 150 * scaleRatio.x * 0.8, windowSize.y / 2.f + length / 5.f - 71.f * scaleRatio.y * 0.8);
	saveGameButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	saveGameButton->setText("Save Game",30);
	saveGameButton->setCallback([this, &context]()
		{
			context.window->close();
			sf::Image icon = context.image->get(Image::Icon);
			context.window->create(sf::VideoMode(909, 909), "TetrisMirror", sf::Style::Close);
			context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			requestStackPush(States::SaveGame);
		});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(windowSize.x / 2.f - 150 * scaleRatio.x * 0.8, windowSize.y / 2 + length / 5);
	exitButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	exitButton->setText("Back To Menu",30);
	exitButton->setCallback([this, &context]()
		{
			requestStateClear();
			sf::Image icon = context.image->get(Image::Icon);
			context.window->close();
			context.window->create(sf::VideoMode(909, 909), "TetrisMirror", sf::Style::Close);
			context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			requestStackPush(States::Menu);
		});



	mGUIContainer.pack(continueGameButton);
	mGUIContainer.pack(saveGameButton);
	mGUIContainer.pack(exitButton);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(glassBackground);
	window.draw(mBackgroundSprite);
	window.draw(mText);
	window.draw(mScore);
	window.draw(mGUIContainer);
}

bool PauseState::update()
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}

	return false;
}
