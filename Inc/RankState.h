#pragma once
#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <queue>
#include <vector>
#include <filesystem>
#include <fstream>

class RankState : public State
{
public:
	typedef std::pair<std::string, int> accountPair;

							RankState(StateStack& stack, Context& context);

	virtual void			draw();
	virtual bool			update();
	virtual bool			handleEvent(const sf::Event& event);

private:
	struct CompareBySecond {
		bool operator()(const accountPair& pair1, const accountPair& pair2) {
			return pair1.second < pair2.second;
		}
	};

	void					scanAccounts();
	void					addAccountRank(Context& context);

private:
	size_t					accountCnt = 0;
	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;

	std::priority_queue<accountPair, std::vector<accountPair>, CompareBySecond>  accountQueue;
	
};
