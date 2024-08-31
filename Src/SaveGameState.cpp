#include <SaveGameState.h>
#include <Label.h>
#include <Saves.h>
#include <Utility.h>
#include <MusicPlayer.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <chrono>
#include <ctime>
#include <memory>

SaveGameState::SaveGameState(StateStack& stack, Context& context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::SettingBackground);
	mBackgroundSprite.setTexture(texture);

	scanSaves();

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(300, 625);
	exitButton->setText("Back");
	exitButton->setCallback([this,&context]()
		{
			context.window->close();
			sf::Image icon = context.image->get(Image::Icon);
			context.window->create(sf::VideoMode(getContext().mSave->getWidth() * 30 + 150, getContext().mSave->getHeight() * 30 + 20), "TetrisMirror", sf::Style::Close);
			context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			requestStackPop();
		});

	mGUIContainer.pack(exitButton);

}

void SaveGameState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SaveGameState::update()
{
	return true;
}

bool SaveGameState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		
		auto context = getContext();
		context.window->close();
		sf::Image icon = context.image->get(Image::Icon);
		context.window->create(sf::VideoMode(getContext().mSave->getWidth() * 30 + 150, getContext().mSave->getHeight() * 30 + 20), "TetrisMirror", sf::Style::Close);
		context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		requestStackPop();
	}

	return false;
}

void SaveGameState::addSaveLabel(const Context& context,size_t saveID, float y, const std::string& time, std::string& score, std::string& width, std::string& height, std::string& speed) {
	auto saveButton = std::make_shared<GUI::Button>(context);
	saveButton->setPosition(150.f, y);
	saveButton->setTexture(context.textures->get(Textures::Save));
	saveButton->setText(" Save"+toString(saveID)+" " + time, 20);
	saveButton->setCallback([this]() 
		{
			saveGame(mGUIContainer.getmSelctedChild()/2+1);
		});

	auto label = std::make_shared<GUI::Label>("Score:"+score+ "  Width:" +width+"  Height:"+height+"  Speed : "+speed, *context.fonts);
	label->setPosition(465.f, y + 34.5);
	mGUIContainer.pack(saveButton);
	mGUIContainer.pack(label);
}


void SaveGameState::scanSaves() {
	for (int i = 1; i <= 6; i++) {
		std::ifstream save("Accounts/"+getContext().mAccount->getUsername() + "/Saves/Save" + toString(i) + ".txt", std::iostream::in);
		if (!save.is_open()) {
			throw std::runtime_error("Accounts::registeAccount - Failed to Scan Save" + toString(i));
		}
		string saveData[5];
		for (int i = 0; i < 5; i++) {
			std::getline(save,saveData[i]);
			saveData[i].erase(0,7);
		}
		addSaveLabel(getContext(),i, 112.f + 74.f * i, saveData[0], saveData[1], saveData[2], saveData[3], saveData[4]);
		save.close();
	}
	return;
}

void SaveGameState::saveGame(size_t saveID) {
	std::ofstream save("Accounts/" + getContext().mAccount->getUsername() + "/Saves/Save" + toString(saveID) + ".txt", std::iostream::out);
	if (!save.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Scan Save" + toString(saveID));
	}
	// Get the current system time
	std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	// Convert it to the local time structure
	std::tm localTime;
	localtime_s(&localTime, &currentTime);


	// Extract the year, month, day, hour, and minute
	int year = localTime.tm_year + 1900;
	int month = localTime.tm_mon + 1;
	int day = localTime.tm_mday;
	int hour = localTime.tm_hour;
	int minute = localTime.tm_min;

	auto mSave = getContext().mSave;

	//convert int to string
	string sTime = toString(year) + "/" + toString(month) + "/" + toString(day) + "/" + toString(hour) + "." + toString(minute);
	string sScore = toString(mSave->getCurrentScore());
	string sWidth = toString(mSave->getWidth());
	string sHeight = toString(mSave->getHeight());
	string sSpeed = toString(mSave->getSpeed());
	string sMagic = toString(mSave->getMagic());
	string sCBID = toString(mSave->getCurrentBlockID());//currentBlockID
	string sNBID = toString(mSave->getNextBlockID());//NextBlockID

	save << "Time  :" + sTime   << std::endl;
	save << "Score :" + sScore  << std::endl;
	save << "Width :" + sWidth  << std::endl;
	save << "Height:" + sHeight << std::endl;
	save << "Speed :" + sSpeed  << std::endl;
	save << "Magic :" + sMagic  << std::endl;
	save << "CBID  :" + sCBID   << std::endl;
	save << "NBID  :" + sNBID << std::endl;
	save << "Table :  "<< std::endl;
	auto mTable = mSave->getTable();
	for (int i = 0; i < mSave->getHeight(); i++) {	
		for (int j = 0; j < mSave->getWidth(); j++) {
			save << toString(mTable[i][j]);
		}
		save << std::endl;
	}
	save.close();

	//update save label
	std::dynamic_pointer_cast<GUI::Label>(mGUIContainer.getChild(2 * saveID - 1))->setText("Score:" + sScore + "  Width:" + sWidth + "  Height:" + sHeight + "  Speed : " + sSpeed,16);
	std::dynamic_pointer_cast<GUI::Button>(mGUIContainer.getChild(saveID * 2 - 2))->setText(" Save" + toString(saveID) + " " + toString(year) + "/" + toString(month) + "/" + toString(day) + "/" + toString(hour) + "." + toString(minute), 20);
	return;
}