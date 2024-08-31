#include <Accounts.h>
#include <CommandQueue.h>
#include <ResourceIdentifiers.h>
#include <Foreach.h>
#include <Utility.h>
#include <GameState.h>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;
using std::string;

Accounts::Accounts()
	:mUsername(""), mPassword(""), bestScore(0), mKeyBinding(),isDarkMode(true),blockStyle(0)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = Spin;
	mKeyBinding[sf::Keyboard::Down] = Speed;
	mKeyBinding[sf::Keyboard::Space] = DropBotton;
	mKeyBinding[sf::Keyboard::M] = Magic;

	// Set initial action bindings
	initializeActions();

}

Accounts::Accounts(string username, string password)
	:mUsername(username), mPassword(password), bestScore(0),mKeyBinding(), isDarkMode(true), blockStyle(0)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = Spin;
	mKeyBinding[sf::Keyboard::Down] = Speed;
	mKeyBinding[sf::Keyboard::Space] = DropBotton;
	mKeyBinding[sf::Keyboard::M] = Magic;

	// Set initial action bindings
	initializeActions();

	
}

Accounts::Status Accounts::registerAccount() {
	string path = "Accounts/" + mUsername;
	//Create Account Folder
	if (!createDirectory(path)) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Create Account Folder " + path);
	}
	//initial Account Setting and set password;
	std::ofstream accountSettingFile(path+"/" + mUsername + "Setting.txt", std::ofstream::out);
	if (!accountSettingFile.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Create Account setting " + path);
	}
	accountSettingFile << "Password:   " << hashString(mPassword) << std::endl;
	accountSettingFile << "MoveLeft:   " << "Left" << std::endl;
	accountSettingFile << "MoveRight:  " << "Right" << std::endl;
	accountSettingFile << "Spin:       " << "Up" << std::endl;
	accountSettingFile << "Speed:      " << "Down" << std::endl;
	accountSettingFile << "DropBotton: " << "Space" << std::endl;
	accountSettingFile << "BestScore:  " << "0" << std::endl;
	accountSettingFile.close();

	//Create Account Saves Folder
	path = path + "/Saves";
	if (!createDirectory(path)) {
		throw std::runtime_error("Accounts::registeAccount - Failed to Create Account Save Folder " + path);
	}

	//Create 6 empty saves
	for (int i = 1; i <= 6; i++) {
		std::ofstream save(path+"/Save"+toString(i)+".txt", std::ofstream::out);
		if (!save.is_open()) {
			throw std::runtime_error("Accounts::registeAccount - Failed to Create Empty Save " + path + "/Save" + toString(i));
		}
		save << "Time  :empty"<<std::endl;
		save << "Score :0"<<std::endl;
		save << "Width :0"<<std::endl;
		save << "Height:0"<<std::endl;
		save << "Speed :0"<<std::endl;
		save << "Magic :0"<<std::endl;
		save << "CBID  :0"<<std::endl;//currentBlockID
		save << "NBID  :0"<<std::endl;//NextBlockID
		save << "Table :  "<<std::endl;

		save.close();
	}

	return Accounts::Status::success;
}


void Accounts::assignKey(ActionID action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}
	
	// Insert new binding
	mKeyBinding[key] = action;
}


Accounts::Status Accounts::loginAccount(string Username,string Password)  {
	mUsername = Username;
	string path = "Accounts/" + Username + "/" + Username + "Setting.txt";
	std::ifstream accountSettingFile(path);
	if (!accountSettingFile.is_open()) {
		return Accounts::Status::accountNotExist;
	}
	string line;

	//check passwords
	std::getline(accountSettingFile, line);
	if (line != ("Password:   " + toString(hashString(Password)))) {
		return Accounts::Status::wrongPassword;
	}

	//Load KeyBinding
	int KeyCount = 0;
	while (KeyCount < 5&&getline(accountSettingFile, line) ) {
		
		line.erase(0, 12); 
		assignKey(Accounts::ActionID(KeyCount++),toKey(line));
	}

	//Load BestScore
	std::getline(accountSettingFile, line);
	line.erase(0, 12);
	setBestScore(toInt(line));
	return Accounts::success;
}

Accounts::Status Accounts::loginAccount(std::pair<string,string>UsernamePassword) {
	return loginAccount(UsernamePassword.first, UsernamePassword.second);
}

void Accounts::writeKeySettings(ActionID action, sf::Keyboard::Key key) {
	string path = "Accounts/" + mUsername + "/" + mUsername + "Setting.txt";
	std::fstream accountSettingFile(path, std::ofstream::in);
	if (!accountSettingFile.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to write key settings" + path);
	}
	std::vector<string>fileCopy(7);
	string line;
	for (int i = 0; i < 7; i++) {
		std::getline(accountSettingFile, line);
		fileCopy[i] = line;
	}
	fileCopy[action + 1].erase(12);
	fileCopy[action + 1].insert(12, toString(key));
	accountSettingFile.close();
	accountSettingFile.open(path, std::ofstream::out|std::ios::trunc);
	if (!accountSettingFile.is_open()) {
		throw std::runtime_error("Accounts::registeAccount - Failed to write key settings" + path);
	}
	for (const std::string& str : fileCopy) {
		accountSettingFile << str << std::endl;
	}

	accountSettingFile.close();

}

 

void Accounts::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end())
			commands.push(mActionBinding[found->second]);
	}
}

sf::Keyboard::Key Accounts::getAssignedKey(ActionID action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Accounts::initializeActions()
{
	mActionBinding[MoveLeft].action = [&](GameState* gamestate) {gamestate->blockmove(sf::Vector2u(-1, 0)); };
	mActionBinding[MoveRight].action = [&](GameState* gamestate) {gamestate->blockmove(sf::Vector2u(1, 0));};
	mActionBinding[Spin].action = [&](GameState* gamestate) {gamestate->spin(); };
	mActionBinding[Speed].action = [&](GameState* gamestate) {gamestate->blockmove(sf::Vector2u(0, 1));};
	mActionBinding[DropBotton].action = [&](GameState* gamestate) {gamestate->dropBotton();};
	mActionBinding[Magic].action = [&](GameState* gamestate) {gamestate->pushMagicState(); };

}


void Accounts::setBestScore(size_t Score) {
	bestScore = Score;
	string path = "Accounts/" + mUsername + "/" + mUsername + "Setting.txt";
	std::fstream accountSettingFile(path, std::ofstream::in);
	if (!accountSettingFile.is_open()) {
		throw std::runtime_error("Accounts::setBestScore - Failed to update player's bestscore" + path);
	}
	std::vector<string>fileCopy(7);
	string line;
	for (int i = 0; i < 7; i++) {
		std::getline(accountSettingFile, line);
		fileCopy[i] = line;
	}
	fileCopy[6].erase(12);
	fileCopy[6].insert(12, toString(bestScore));
	accountSettingFile.close();
	accountSettingFile.open(path, std::ofstream::out | std::ios::trunc);
	if (!accountSettingFile.is_open()) {
		throw std::runtime_error("Accounts::setBestScore - Failed to update player's bestscore" + path);
	}
	for (const std::string& str : fileCopy) {
		accountSettingFile << str << std::endl;
	}
	accountSettingFile.close();
	return;
}

size_t Accounts::getBestScore() const{
	return bestScore;
}

size_t Accounts::getBlockStyle() const {
	return blockStyle;
}

void Accounts::setBlockStyle(size_t style) {
	blockStyle = style;
}
string Accounts::getUsername() const {
	return mUsername;
}

void Accounts::setDarkMode(bool flag) {
	isDarkMode = flag;
}
bool Accounts::getDarkMode()const {
	return isDarkMode;
}
