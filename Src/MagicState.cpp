#include <MagicState.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>
#include <SFML/Graphics/RenderWindow.hpp>


MagicState::MagicState(StateStack& stack, Context& context)
	: State(stack, context)
	, mGUIContainer()
	,blockNum(1)
{

	//calculate rational transform 
	sf::Vector2u windowSize = context.window->getSize();
	unsigned int length = std::min(windowSize.x, windowSize.y) / 3.f * 2.f;
	sf::Vector2f scaleRatio;
	scaleRatio.x = scaleRatio.y = float(length) / 300.f;

	//set frosted glass background
	glassBackground.setSize(sf::Vector2f(context.window->getSize().x, context.window->getSize().y));
	glassBackground.setFillColor(sf::Color(0, 0, 0, 128));


	sf::Texture& texture = context.textures->get(Textures::MagicBackground);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setPosition((windowSize.x - length) / 2.f, (windowSize.y - length) / 2.f);
	mBackgroundSprite.setScale(scaleRatio);
	mBlockSprite.setTexture(context.textures->get(Textures::BlocksSkin));

	auto previousBlockButton = std::make_shared<GUI::Button>(context);
	previousBlockButton->setPosition(windowSize.x / 2.f - 150 * scaleRatio.x * 0.8, windowSize.y / 2.f + length / 5.f - 71.f * scaleRatio.y * 0.8);
	previousBlockButton->setScale(scaleRatio.x * 0.2, scaleRatio.y * 0.8);
	previousBlockButton->setText("", 30);
	previousBlockButton->setTexture(context.textures->get(Textures::LeftArrow));
	previousBlockButton->setCallback([this, &context]()
		{
			blockNum = blockNum % 7 + 1;
		});

	auto nextBlockButton = std::make_shared<GUI::Button>(context);
	nextBlockButton->setPosition(windowSize.x / 2.f + 150 * scaleRatio.x * 0.8- 300*scaleRatio.x * 0.2, windowSize.y / 2.f + length / 5.f - 71.f * scaleRatio.y * 0.8);
	nextBlockButton->setScale(scaleRatio.x * 0.2, scaleRatio.y * 0.8);
	nextBlockButton->setText("", 30);
	nextBlockButton->setTexture(context.textures->get(Textures::RightArrow));
	nextBlockButton->setCallback([this, &context]()
		{
			blockNum = blockNum==1?7:blockNum-1;
		});


	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(windowSize.x / 2.f - 150 * scaleRatio.x * 0.8, windowSize.y / 2 + length / 5);
	exitButton->setScale(scaleRatio.x * 0.8, scaleRatio.y * 0.8);
	exitButton->setText("Confirm", 30);
	exitButton->setCallback([this, &context]()
		{
			context.mSave->setNextBlockID(Blocks::ID(this->blockNum));
			requestStackPop();
		});


	mGUIContainer.pack(previousBlockButton);
	mGUIContainer.pack(nextBlockButton);
	mGUIContainer.pack(exitButton);
}

void MagicState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(glassBackground);
	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	mBlockSprite.setTextureRect(sf::IntRect((blockNum - 1) * 30, 0, 30, 30));
	for (int i = 0; i < 4; i++)
	{
		mBlockSprite.setPosition((Blocks::blocks[blockNum - 1][i]) % 2 * 30.f +getContext().window->getSize().x / 2.3, (Blocks::blocks[blockNum - 1][i]) / 2 * 30.f + getContext().window->getSize().y / 2.6);
		window.draw(mBlockSprite);
	}
	
}

bool MagicState::update()
{
	return false;
}

bool MagicState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		getContext().mSave->setNextBlockID(Blocks::None);
		requestStackPop();
	}
	return false;
}
