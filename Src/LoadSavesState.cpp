#include <LoadSavesState.h>
#include <Button.h>
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

LoadSavesState::LoadSavesState(StateStack& stack, Context& context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::SettingBackground);
	mBackgroundSprite.setTexture(texture);

	scanSaves();

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(300, 625);
	exitButton->setText("Back");
	exitButton->setCallback([this, &context]()
		{
			requestStackPop();
		});

	mGUIContainer.pack(exitButton);

}

void LoadSavesState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool LoadSavesState::update()
{
	return true;
}

bool LoadSavesState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) {
		deleteSave();
	}
	return false;
}
void LoadSavesState::addSaveLabel(const Context& context, size_t saveID, float y, const std::string& time, std::string& score, std::string& width, std::string& height, std::string& speed) {
	auto saveButton = std::make_shared<GUI::Button>(context);
	saveButton->setPosition(150.f, y);
	saveButton->setText(" Save" + toString(saveID) + " " + time, 20);
	saveButton->setTexture(context.textures->get(Textures::Save));
	saveButton->setCallback([this]()
		{
			loadSave(mGUIContainer.getmSelctedChild() / 2 + 1);
			requestStackPop();
			requestStackPush(States::Game);
		});

	auto label = std::make_shared<GUI::Label>("Score:" + score + "  Width:" + width + "  Height:" + height + "  Speed : " + speed, *context.fonts);
	label->setPosition(465.f, y + 34.5);
	mGUIContainer.pack(saveButton);
	mGUIContainer.pack(label);
}


void LoadSavesState::scanSaves() {
	for (int i = 1; i <= 6; i++) {
		std::ifstream save("Accounts/" + getContext().mAccount->getUsername() + "/Saves/Save" + toString(i) + ".txt", std::iostream::in);
		if (!save.is_open()) {
			throw std::runtime_error("Accounts::registeAccount - Failed to Scan Save" + toString(i));
		}
		string saveData[5];
		for (int i = 0; i < 5; i++) {
			std::getline(save, saveData[i]);
			saveData[i].erase(0, 7);
		}
		addSaveLabel(getContext(), i, 112.f + 74.f * i, saveData[0], saveData[1], saveData[2], saveData[3], saveData[4]);
		save.close();
	}
	return;
}

void LoadSavesState::deleteSave() {
	size_t saveID = mGUIContainer.getmSelctedChild()/2+1;
	if (saveID == 7)
		return;
	std::ofstream save("Accounts/" + getContext().mAccount->getUsername() + "/Saves/Save" + toString(saveID) + ".txt", std::iostream::out);
	if (!save.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Scan Save" + toString(saveID));
	}
	save << "Time  :empty" << std::endl;
	save << "Score :0" << std::endl;
	save << "Width :0" << std::endl;
	save << "Height:0" << std::endl;
	save << "Speed :0" << std::endl;
	save << "Magic :0" << std::endl;
	save << "CBID  :0" << std::endl;//currentBlockID
	save << "NBID  :0" << std::endl;//NextBlockID
	save << "Table :  " << std::endl;
	save.close();
	//update save label
	std::dynamic_pointer_cast<GUI::Label>(mGUIContainer.getChild(2 * saveID - 1))->setText("Score:0  Width:0  Height:0  Speed : 0" , 16);
	std::dynamic_pointer_cast<GUI::Button>(mGUIContainer.getChild(saveID * 2 - 2))->setText(" Save" + toString(saveID) + " empty", 20);
	return;
}

void LoadSavesState::loadSave(size_t saveID) {
	std::ifstream save("Accounts/" + getContext().mAccount->getUsername() + "/Saves/Save" + toString(saveID) + ".txt", std::ios::in);
	if (!save.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Load Save" + toString(saveID));
	}

	auto mSave = getContext().mSave;
	string line;
	std::getline(save, line);//skip time line
	//load score
	std::getline(save, line);
	mSave->setCurrentScore(toInt(line.erase(0, 7)));
	//load width
	std::getline(save, line);
	mSave->setWidth(toInt(line.erase(0, 7)));
	//load height
	std::getline(save, line);
	mSave->setHeight(toInt(line.erase(0, 7)));
	//load speed
	std::getline(save, line);
	mSave->setSpeed(toInt(line.erase(0, 7)));
	//load magic
	std::getline(save, line);
	mSave->setMagic(toInt(line.erase(0, 7)));
	//load CurrentBlockID
	std::getline(save, line);
	mSave->setCurrentBlockID(Blocks::ID(toInt(line.erase(0, 7))));
	//load NextBlockID
	std::getline(save, line);
	mSave->setNextBlockID(Blocks::ID(toInt(line.erase(0, 7))));
	//load Table
	std::getline(save, line);
	std::vector<std::vector<Blocks::ID>> table;
	table.resize(mSave->getHeight(), std::vector<Blocks::ID>(mSave->getWidth(), Blocks::ID::None));
	for (int i = 0; i < mSave->getHeight(); i++) {
		std::getline(save, line);
		for (int j = 0; j < mSave->getWidth(); j++) {
			table[i][j] = Blocks::ID(line[j]-'0');
		}
	}
	mSave->setTable(table);
	save.close();
	return;
}
