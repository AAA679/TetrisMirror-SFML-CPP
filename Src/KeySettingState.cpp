#include <KeySettingState.h>
#include <Utility.h>
#include <ResourceHolder.h>
#include <Label.h>

#include <SFML/Graphics/RenderWindow.hpp>


KeySettingsState::KeySettingsState(StateStack& stack, Context &context)
	: State(stack, context)
	, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::SettingBackground));
	mBlockSprite.setTexture(context.textures->get(Textures::BlocksSkin));
	mBlockSprite.setPosition(460, 652);
	// Build key binding buttons and labels
	addButtonLabel(Accounts::MoveLeft , 186.f, "Move Left", context);
	addButtonLabel(Accounts::MoveRight, 260.f, "Move Right", context);
	addButtonLabel(Accounts::Spin,	  334.f, "Spin",context);
	addButtonLabel(Accounts::Speed,	  408.f, "Speed", context);
	addButtonLabel(Accounts::DropBotton,482.f, "DropBotton", context);

	updateLabels();

	auto musicButton = std::make_shared<GUI::Button>(context);
	musicButton->setTexture(context.textures->get(Textures::Buttons));
	musicButton->setSpriteScale(0.5f, 1.f);
	musicButton->setPosition(150, 556);
	musicButton->setTextPosition(75, 35.5f);
	musicButton->setText("Music: ON", 25);
	musicButton->setTextStyle(sf::Text::Italic);
	musicButton->setCallback([&context,this, musicButton]()
		{	
			if (context.music->getMute()) {
				context.music->play(context.music->getCurrentMusic());
				musicButton->setText("Music: ON", 25);
			}
			else {
				context.music->stop();
				musicButton->setText("Music: OFF", 25);
			}
			musicButton->deactivate();
		});

	auto musicChangeButton = std::make_shared<GUI::Button>(context);
	musicChangeButton->setTexture(context.textures->get(Textures::Buttons));
	musicChangeButton->setPosition(300, 556);
	musicChangeButton->setText("Music:"+toString(context.music->getCurrentMusic()), 25);
	musicChangeButton->setTextStyle(sf::Text::Italic);
	musicChangeButton->setCallback([&context, this, musicChangeButton]()
		{
			if (context.music->getCurrentMusic() == Music::Distance) {
				context.music->setCurrentMusic(Music::MirrorOfEdge);
			}
			else {
				context.music->setCurrentMusic(Music::ID(int(context.music->getCurrentMusic())+1));
			}
			musicChangeButton->setText("Music:" + toString(context.music->getCurrentMusic()), 25);	
			if (!context.music->getMute()) {
				context.music->stop();
				context.music->play(context.music->getCurrentMusic());
			}
		});

	auto soundButton = std::make_shared<GUI::Button>(context);
	soundButton->setTexture(context.textures->get(Textures::Buttons));
	soundButton->setSpriteScale(0.5f, 1.f);
	soundButton->setPosition(600, 556);
	soundButton->setTextPosition(75, 35.5f);
	soundButton->setText("Sound: ON", 25);
	soundButton->setTextStyle(sf::Text::Italic);
	soundButton->setCallback([&context, this, soundButton]()
		{
			if (context.sounds->getMute()) {
				soundButton->setText("Sound: ON", 25);
			}
			else {
				soundButton->setText("Sound: OFF", 25);
			}
			context.sounds->setMute();
		});

	auto backgroundButton = std::make_shared<GUI::Button>(context);
	backgroundButton->setTexture(context.textures->get(Textures::Buttons));
	backgroundButton->setSpriteScale(0.5f, 1.f);
	backgroundButton->setPosition(150, 630);
	backgroundButton->setTextPosition(75, 35.5f);
	backgroundButton->setText(context.mAccount->getDarkMode()?"Dark Mode:ON": "Dark Mode:OFF", 19);
	backgroundButton->setTextStyle(sf::Text::Italic);
	backgroundButton->setCallback([&context, this, backgroundButton]()
		{
			if (context.mAccount->getDarkMode()==true) {
				backgroundButton->setText("Dark Mode:OFF", 19);
				context.mAccount->setDarkMode(false);
				context.textures->load(Textures::GameTableBackground, "Media/Textures/gameTableBackground1.png");
				context.textures->load(Textures::GameGUIBackground, "Media/Textures/gameGUIBackground1.png");
				context.textures->load(Textures::GameNextBlockBackground, "Media/Textures/gameNextBlockBackground1.png");
			}
			else {
				backgroundButton->setText("Dark Mode:ON", 19);
				context.mAccount->setDarkMode(true);
				context.textures->load(Textures::GameTableBackground, "Media/Textures/gameTableBackground.png");
				context.textures->load(Textures::GameGUIBackground, "Media/Textures/gameGUIBackground.png");
				context.textures->load(Textures::GameNextBlockBackground, "Media/Textures/gameNextBlockBackground.png");
			}
		});

	auto blockStyleButton = std::make_shared<GUI::Button>(context);
	blockStyleButton->setTexture(context.textures->get(Textures::Buttons));
	blockStyleButton->setSpriteScale(0.5f, 1.f);
	blockStyleButton->setPosition(300, 630);
	blockStyleButton->setTextPosition(75, 35.5f);
	blockStyleButton->setText("BlockStyle: "+toString(context.mAccount->getBlockStyle()), 19);
	blockStyleButton->setTextStyle(sf::Text::Italic);
	blockStyleButton->setCallback([&context, this, blockStyleButton]()
		{
			switch (context.mAccount->getBlockStyle())
			{
			case 0:
				context.mAccount->setBlockStyle(1);
				context.textures->load(Textures::BlocksSkin, "Media/Textures/BlocksSkin1.png");
				blockStyleButton->setText("BlockStyle: 1", 19);
				break;
			case 1:
				context.mAccount->setBlockStyle(2);
				context.textures->load(Textures::BlocksSkin, "Media/Textures/BlocksSkin2.png");
				blockStyleButton->setText("BlockStyle: 2" , 19);
				break;
			case 2:
				context.mAccount->setBlockStyle(0);
				context.textures->load(Textures::BlocksSkin, "Media/Textures/BlocksSkin0.png");
				blockStyleButton->setText("BlockStyle: 0", 19);
				break;
			}
			mBlockSprite.setTexture(context.textures->get(Textures::BlocksSkin));
		});

	auto resetButton = std::make_shared<GUI::Button>(context);
	resetButton->setTexture(context.textures->get(Textures::Buttons));
	resetButton->setSpriteScale(0.5f, 1.f);
	resetButton->setPosition(150, 710);
	resetButton->setTextPosition(75, 35.5f);
	resetButton->setText("Reset Key", 25);
	resetButton->setTextStyle(sf::Text::Italic);
	resetButton->setCallback([&context,this]()
		{
			context.mAccount->assignKey(static_cast<Accounts::ActionID>(Accounts::MoveLeft), sf::Keyboard::Left);
			context.mAccount->writeKeySettings(static_cast<Accounts::ActionID>(Accounts::MoveLeft), sf::Keyboard::Left);
			context.mAccount->assignKey(static_cast<Accounts::ActionID>(Accounts::MoveRight), sf::Keyboard::Right);
			context.mAccount->writeKeySettings(static_cast<Accounts::ActionID>(Accounts::MoveRight), sf::Keyboard::Right);
			context.mAccount->assignKey(static_cast<Accounts::ActionID>(Accounts::Spin), sf::Keyboard::Up);
			context.mAccount->writeKeySettings(static_cast<Accounts::ActionID>(Accounts::Spin), sf::Keyboard::Up);
			context.mAccount->assignKey(static_cast<Accounts::ActionID>(Accounts::Speed), sf::Keyboard::Down);
			context.mAccount->writeKeySettings(static_cast<Accounts::ActionID>(Accounts::Speed), sf::Keyboard::Down);
			context.mAccount->assignKey(static_cast<Accounts::ActionID>(Accounts::DropBotton), sf::Keyboard::Space);
			context.mAccount->writeKeySettings(static_cast<Accounts::ActionID>(Accounts::DropBotton), sf::Keyboard::Space);
			updateLabels();
		});


	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(400.f, 710.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&KeySettingsState::requestStackPop, this));

	mGUIContainer.pack(musicButton);
	mGUIContainer.pack(musicChangeButton);
	mGUIContainer.pack(soundButton);
	mGUIContainer.pack(backgroundButton);
	mGUIContainer.pack(blockStyleButton);
	mGUIContainer.pack(resetButton);
	mGUIContainer.pack(backButton);
}

void KeySettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mBlockSprite);
	window.draw(mGUIContainer);
}

bool KeySettingsState::update()
{
	return true;
}

bool KeySettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Accounts::ActionCount-1; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().mAccount->assignKey(static_cast<Accounts::ActionID>(action), event.key.code);
				getContext().mAccount->writeKeySettings(static_cast<Accounts::ActionID>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}


	return false;
}


void KeySettingsState::updateLabels()
{
	Accounts& account = *getContext().mAccount;

	for (std::size_t i = 0; i < Accounts::ActionCount-1; ++i)
	{
		sf::Keyboard::Key key = account.getAssignedKey(static_cast<Accounts::ActionID>(i));
		mBindingLabels[i]->setText("Now binding key: "+toString(key),25);
	}
}


void KeySettingsState::addButtonLabel(Accounts::ActionID action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(context);
	mBindingButtons[action]->setPosition(150.f, y);
	mBindingButtons[action]->setText(text,30);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(455.f, y+34.5);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
