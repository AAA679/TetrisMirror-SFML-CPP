#pragma once
#include <fstream>
#include <string>
#include <map>

#include <Command.h>


#include <SFML/Window/Event.hpp>

using std::string;

class CommandQueue;
class Accounts {
public:
	typedef		std::shared_ptr<Accounts> Ptr;

	enum ActionID
	{
		MoveLeft,
		MoveRight,
		Spin,
		Speed,
		DropBotton,
		Magic,
		ActionCount
	};
	enum Status
	{
		wating,
		success,
		accountNotExist,
		wrongPassword
	};

							Accounts();
							Accounts(string username, string password);

	Status					registerAccount();
	Status					loginAccount(std::pair<string, string>);
	Status					loginAccount(string username, string password);

	void					writeKeySettings(ActionID, sf::Keyboard::Key);

	void					handleEvent(const sf::Event& event, CommandQueue& commands); 


	void					assignKey(ActionID action, sf::Keyboard::Key key);
	sf::Keyboard::Key		getAssignedKey(ActionID action) const;

	void					setBestScore(size_t Score);
	size_t					getBestScore() const;

	string					getUsername() const;

	void					setDarkMode(bool flag);
	bool					getDarkMode()const;

	void					setBlockStyle(size_t style);
	size_t					getBlockStyle() const;
private:
	void					initializeActions();

private:
	string					mUsername;
	string					mPassword;
	size_t					bestScore;
	size_t					blockStyle;
	bool					isDarkMode;
	std::map<sf::Keyboard::Key, ActionID>		mKeyBinding;
	std::map<ActionID, Command>				    mActionBinding;


};