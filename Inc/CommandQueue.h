#pragma once

#include <Command.h>

#include <queue>


class CommandQueue
{
public:

	void						push(const Command& command);
	Command						pop();
	bool						isEmpty() const;
	void						clear();

private:
	std::queue<Command>			mQueue;
};
