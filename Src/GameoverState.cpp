#include <GameoverState.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>
#include <SFML/Graphics/RenderWindow.hpp>


GameoverState::GameoverState(StateStack& stack, Context& context)
	: State(stack, context)
	, mText("", context.fonts->get(Fonts::Main), 25)
	, mScore("", context.fonts->get(Fonts::Main), 25)
	, mGUIContainer()
{

	//calculate rational transform 
	sf::Vector2u windowSize=context.window->getSize();
	unsigned int length = std::min(windowSize.x, windowSize.y)/3.f*2.f;
	sf::Vector2f scaleRatio;
	scaleRatio.x=scaleRatio.y = float(length) / 300.f;

	//set frosted glass background
	glassBackground.setSize(sf::Vector2f(context.window->getSize().x, context.window->getSize().y));
	glassBackground.setFillColor(sf::Color(0, 0, 0, 128)); 

	//Set final score
	mText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f- length / 5.f+20 * scaleRatio.x);
	mText.setString("Final Score:");
	mText.setFillColor(sf::Color::White);
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(2.4f);
	mText.setScale(scaleRatio);
	centerOrigin(mText);

	mScore.setPosition(windowSize.x / 2.f, windowSize.y / 2.f- length / 5.f+ 45*scaleRatio.x);
	mScore.setString(toString(context.mSave->getCurrentScore()));
	mScore.setFillColor(sf::Color::White);
	mScore.setOutlineColor(sf::Color::Black);
	mScore.setOutlineThickness(2.4f);
	mScore.setScale(scaleRatio);
	centerOrigin(mScore);


	sf::Texture& texture = context.textures->get(Textures::GameoverBackground);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setPosition((windowSize.x - length) / 2.f, (windowSize.y - length) / 2.f);
	mBackgroundSprite.setScale(scaleRatio);

	auto newGameButton = std::make_shared<GUI::Button>(context);
	newGameButton->setPosition(windowSize.x / 2.f - 150* scaleRatio.x * 0.8, windowSize.y/2.f );
	newGameButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	newGameButton->setText("New Round");
	newGameButton->setCallback([this, &context]()
		{
			context.mSave->resetTable();
			requestStateClear();
			requestStackPush(States::Game);
		});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(windowSize.x/2.f - 150* scaleRatio.x * 0.8, windowSize.y / 2 + length / 5);
	exitButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	exitButton->setText("Back");
	exitButton->setCallback([this,&context]()
		{
			requestStateClear();
			sf::Image icon = context.image->get(Image::Icon);
			context.window->close();
			context.window->create(sf::VideoMode(909,909), "TetrisMirror", sf::Style::Close);
			context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			requestStackPush(States::Menu);
		});



	mGUIContainer.pack(newGameButton);
	mGUIContainer.pack(exitButton);
}

void GameoverState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(glassBackground);
	window.draw(mBackgroundSprite);
	window.draw(mText);
	window.draw(mScore);
	window.draw(mGUIContainer);
}

bool GameoverState::update()
{
	return false;
}

bool GameoverState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
