#pragma once


#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

class GameState;

struct Command
{
	typedef std::function<void(GameState*)> Action;

	Command();

	Action						action;

};



