#include <RankState.h>
#include <Button.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>


RankState::RankState(StateStack& stack, Context& context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::RankBackground);
	texture.setRepeated(true);//Texture auto reuse
	mBackgroundSprite.setTexture(texture);

	scanAccounts();
	addAccountRank(context);

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(300, 50 + (accountCnt + 1) * 71);
	exitButton->setText("Back");
	exitButton->setCallback([this]()
		{
			requestStackPop();
			requestStackPush(States::Menu);
		});


	mGUIContainer.pack(exitButton);

}

void RankState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool RankState::update()
{
	return true;
}

bool RankState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}
	return false;
}


void RankState::scanAccounts() {
	string path = "Accounts";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::is_directory(entry.status()))
		{
			accountPair currentAc;
			//Get the Username of Account
			currentAc.first = entry.path().filename().string();
			std::ifstream accountFile("Accounts/" + currentAc.first + "/" + currentAc.first + "Setting.txt", std::ios::in);
			if (!accountFile.is_open()) {
				throw std::runtime_error("RankState::scanAccounts - Failed to open accountSetting File " + path);
			}
			//Get the Bestscore of Account
			string line;
			for (int i = 1; i <= 7; i++)
				std::getline(accountFile, line);
			line.erase(0, 12);
			currentAc.second = toInt(line);
			accountQueue.emplace(currentAc);
			accountFile.close();
		}
	}
}

void RankState::addAccountRank(Context& context) {
	while (!accountQueue.empty())
	{
		auto account = accountQueue.top();
		accountQueue.pop();
		auto namecard = std::make_shared<GUI::Button>(context);
		namecard->setPosition(300, 50 + (accountCnt++) * 71);
		namecard->setTexture(context.textures->get(Textures::Rank));
		namecard->changeFont();//Change button font to Input Font
		namecard->setText("RANK" + toString(accountCnt) + ": " + account.first + "  Bestscore:" + toString(account.second), 20);
		namecard->setCallback([]()
			{
				//open his goal show states
			});
		mGUIContainer.pack(namecard);
	}

}
