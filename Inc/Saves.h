#pragma once
#include <ResourceIdentifiers.h>


#include <fstream>
#include <vector>

class Saves
{
public:
	typedef				std::shared_ptr<Saves> Ptr;

						Saves(unsigned int width,unsigned int height, unsigned int speed);

	void				setWidth(unsigned int);
	unsigned int		getWidth() const;
	void				setHeight(unsigned int);
	unsigned int		getHeight() const;
	void				setSpeed(unsigned int);
	unsigned int		getSpeed() const;
	void				setCurrentScore(unsigned int);
	unsigned int		getCurrentScore() const;
	void				setCurrentBlockID(Blocks::ID ID);
	Blocks::ID			getCurrentBlockID() const;
	void				setNextBlockID(Blocks::ID ID);
	Blocks::ID			getNextBlockID() const;
	void				setMagic(unsigned int);
	unsigned int		getMagic() const;
	void				setTable(std::vector<std::vector<Blocks::ID>>);
	void				resetTable();
	std::vector<std::vector<Blocks::ID>> getTable() const;

private:
	unsigned int		width;
	unsigned int		height;
	unsigned int		speed;
	unsigned int		magic;
	size_t				currentScore;
	Blocks::ID			currentBlockID;
	Blocks::ID			nextBlockID;

	std::vector<std::vector<Blocks::ID>>	table;
};
