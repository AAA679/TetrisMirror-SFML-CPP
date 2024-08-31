#include <Saves.h>

Saves::Saves(unsigned int width, unsigned int height, unsigned int speed)
    :  width(width),
    height(height),
    speed(speed),
    magic(0),
    currentScore(0),
    currentBlockID(Blocks::ID::None),
    nextBlockID(Blocks::ID::None)
{
    // initial table  10x20 
    table.resize(height, std::vector<Blocks::ID>(width, Blocks::ID::None));
}

void Saves::setWidth(unsigned int Width) { width = Width; };

unsigned int Saves::getWidth() const { return width; };

void Saves::setHeight(unsigned int Height) { height = Height; };

unsigned int Saves::getHeight() const { return height; };

void Saves::setSpeed(unsigned int Speed) { speed = Speed; };

unsigned int Saves::getSpeed() const { return speed; };

void Saves::setCurrentScore(unsigned int score) { currentScore = score; };

unsigned int Saves::getCurrentScore() const { return currentScore; };

void Saves::setMagic(unsigned int Magic) { magic = Magic; };

unsigned int Saves::getMagic() const { return magic; };

void Saves::setCurrentBlockID(Blocks::ID ID) { currentBlockID = ID; };

Blocks::ID	Saves::getCurrentBlockID() const {return currentBlockID;};

void	Saves::setNextBlockID(Blocks::ID ID) { nextBlockID = ID; };

Blocks::ID	Saves::getNextBlockID() const { return nextBlockID; };

std::vector<std::vector<Blocks::ID>> Saves::getTable() const { return table; };


void Saves::setTable(std::vector<std::vector<Blocks::ID>> tp) {
    table = tp;
    table.shrink_to_fit();
};

void Saves::resetTable() {
    table.clear();
    table.resize(height, std::vector<Blocks::ID>(width, Blocks::ID::None));
    setCurrentScore(0);//reset the score
};





