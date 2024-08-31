#include <GameState.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>




GameState::GameState(StateStack& stack, Context &context)
	: State(stack, context)
	, mSave(context.mSave)
	, mSound(*context.sounds)
	, width(mSave->getWidth())
	, height(mSave->getHeight())
	, speed(mSave->getSpeed())
	, magic(mSave->getMagic())
	, useMagic(false)
	, currentScore(mSave->getCurrentScore())
	, currentBlockID(mSave->getCurrentBlockID())
	, nextBlockID(mSave->getNextBlockID())
	, blockGenerateInterval(sf::seconds(1) / float(speed))
	, mCommandQueue()
	, comboDispaly(false)
	, initNextBlockID(false)
{
	//calculate the scale ratio to fix the user-defined width and height
	sf::Vector2f scaleRatio;
	scaleRatio.x = float(width * blockSize) / 1000.f + margin*1.0 /1000.f;
	scaleRatio.y = float(height * blockSize) / 1000.f + margin*1.0 / 1000.f;


	//Change the window  size with the user-defined size
	sf::Image icon = context.image->get(Image::Icon);
	context.window->close();
	context.window->create(sf::VideoMode(width * blockSize+ margin+120, height * blockSize + margin), "TetrisMirror", sf::Style::Close);
	context.window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//set texture for all sprites
	mTableSprite.setTexture(context.textures->get(Textures::GameTableBackground));
	mGUISprite.setTexture(context.textures->get(Textures::GameGUIBackground));
	mNextBlockSprite.setTexture(context.textures->get(Textures::GameNextBlockBackground));
	mBlockSprite.setTexture(context.textures->get(Textures::BlocksSkin));
	mMagicSprite.setTexture(context.textures->get(Textures::MagicBlock));

	//set transform for sprites
	mTableSprite.setScale(scaleRatio);
	mGUISprite.setScale(1, (height * 1.0 - 4.f) / 15.f-0.02);
	mNextBlockSprite.setPosition(width * blockSize + margin, 0);
	mGUISprite.setPosition(width * blockSize + margin, 150);
	mMagicSprite.setPosition(width * blockSize + margin + 30, context.window->getSize().y/2);

	//set random number seed
	srand(static_cast<unsigned int>(time(0)));

	//load save table
	mTable = mSave->getTable();
	mTable.shrink_to_fit();

	//calculate the gamegrade decided by the width, height and speed
	gamegrade = (((double)width / (double)10) * 5 + ((double)20 / (double)height) * 5) * (double)speed * (double)10;

	//initial first block
	if (mSave->getCurrentBlockID() == Blocks::None) 
		currentBlockID = Blocks::ID(1 + rand() % 7);
	for (int i = 0; i < 4; i++)
	{
			currentBlockPos[i].x = (Blocks::blocks[currentBlockID - 1][i]) % 2+width/2-1;
			currentBlockPos[i].y = (Blocks::blocks[currentBlockID - 1][i]) / 2;
	}

	//initial  text
	mCurrentScoreText.setFont(State::getContext().fonts->get(Fonts::Main));
	mCurrentScoreText.setString("Current Score");
	mCurrentScoreText.setCharacterSize(13);
	mCurrentScoreText.setFillColor(sf::Color(66, 255, 164));
	mCurrentScoreText.setPosition(width * blockSize + margin + 60, 190);
	centerOrigin(mCurrentScoreText);

	mCurrentScoreNumText.setFont(State::getContext().fonts->get(Fonts::Main));
	mCurrentScoreNumText.setString(toString(mSave->getCurrentScore()));
	mCurrentScoreNumText.setCharacterSize(25);
	mCurrentScoreNumText.setOutlineColor(sf::Color::Black);
	mCurrentScoreNumText.setOutlineThickness(1.5f);
	mCurrentScoreNumText.setFillColor(sf::Color(66, 255, 164));
	mCurrentScoreNumText.setPosition(width * blockSize + margin + 60,210);
	centerOrigin(mCurrentScoreNumText);

	mBestScoreText.setFont(State::getContext().fonts->get(Fonts::Main));
	mBestScoreText.setString("Best Score");
	mBestScoreText.setFillColor(sf::Color(218, 109, 228));
	mBestScoreText.setCharacterSize(17);
	mBestScoreText.setPosition(width * blockSize + margin + 60, 240);
	centerOrigin(mBestScoreText);

	mBestScoreNumText.setFont(State::getContext().fonts->get(Fonts::Main));
	mBestScoreNumText.setString(toString(getContext().mAccount->getBestScore()));
	mBestScoreNumText.setCharacterSize(25);
	mBestScoreNumText.setFillColor(sf::Color(218, 109, 228));
	mBestScoreNumText.setOutlineColor(sf::Color::Black);
	mBestScoreNumText.setOutlineThickness(1.5f);
	mBestScoreNumText.setPosition(width * blockSize + margin + 60, 260);
	centerOrigin(mBestScoreNumText);

	mMagicText.setFont(State::getContext().fonts->get(Fonts::Main));
	mMagicText.setString("Magic Block\n  (Press \"M\")");
	mMagicText.setFillColor(sf::Color(245, 109, 50));
	mMagicText.setCharacterSize(15);
	mMagicText.setPosition(width * blockSize + margin + 60, context.window->getSize().y / 2+80);
	centerOrigin(mMagicText);

	mMagicNumText.setFont(State::getContext().fonts->get(Fonts::Main));
	mMagicNumText.setString(toString(magic));
	mMagicNumText.setFillColor(sf::Color(245, 109, 50));
	mMagicNumText.setCharacterSize(25);
	mMagicNumText.setPosition(width * blockSize + margin + 60, context.window->getSize().y / 2 + 110);
	centerOrigin(mMagicNumText);

	mComboText.setFont(State::getContext().fonts->get(Fonts::Main));
	mComboText.setString("Combo X0");
	mComboText.setFillColor(sf::Color(156, 173, 24));
	mComboText.setCharacterSize(18);
	mComboText.setOutlineThickness(2.f);
	mComboText.setPosition(width * blockSize + margin + 60, context.window->getSize().y / 2 + 140);
	centerOrigin(mComboText);

}


bool GameState::handleEvent(const sf::Event& event)
{

	getContext().mAccount->handleEvent(event,mCommandQueue);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || event.type == sf::Event::LostFocus) {
		requestStackPush(States::Pause);
		copyData();//Prepare to save game
	}
	
	return false;
}

bool GameState::update() {

	//update game
	blockTimer += gameClock.getElapsedTime();
	gameClock.restart();//restart 

	//judge whether use magic
	if (useMagic) {
		if (mSave->getNextBlockID() == Blocks::None)
			magic++;//Use magic failed
		else {
			initNextBlockID = true;
			nextBlockID = mSave->getNextBlockID();
		}
		useMagic = false;
	}

	//Execute commands
	while (!mCommandQueue.isEmpty()) {
		mCommandQueue.pop().action(this);
	}


	if (blockTimer > blockGenerateInterval)
	{
		drop();
		blockTimer = sf::seconds(0);
	}

	clean();

	//check game failed
	if (!checkFail())
	{
		requestStackPush(States::GameOver);
	}

	//update Data Panel
	mCurrentScoreNumText.setString(toString(currentScore));
	mSave->setCurrentScore(currentScore);
	centerOrigin(mCurrentScoreNumText);//keep num centered after modify the text length
	if (currentScore > getContext().mAccount->getBestScore()) {
		getContext().mAccount->setBestScore(currentScore);
		mBestScoreNumText.setString(toString(currentScore));
		centerOrigin(mBestScoreNumText);
	}

	//remove stopped sounds to avoid out of ram limit
	updateSounds();

	return true;
}


void GameState::updateSounds()
{
	getContext().sounds->removeStoppedSounds();
}

bool GameState::checkFail() const {
	for (int i = 0; i < width; i++)
		if (mTable[1][i])
			return false;
	return true;
}


void GameState::clean()
{
	static size_t accumulateLines=0;
	size_t cleanLines = 0;
	int k = height - 1;
	for (int i = height - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = width - 1; j >= 0; j--)
		{
			if (mTable[i][j] != 0)
			{
				count++;
			}
			mTable[k][j] = mTable[i][j];
		}
		if (count < width)
			k--;
		else {
			++cleanLines;
			mSound.play(SoundEffect::LineClear);
		}
	}
	magic += (accumulateLines + cleanLines) / 5;
	mMagicNumText.setString(toString(magic));
	accumulateLines= (accumulateLines + cleanLines) % 5;
	if (cleanLines > 1) {
		mSound.play(SoundEffect::Combo);
		comboClock.restart();
		comboTimer = sf::Time::Zero;
		mComboText.setString("Combo X" + toString(cleanLines));
		centerOrigin(mComboText);
		comboDispaly = true;
	}
	currentScore += cleanLines * cleanLines * gamegrade;

}


void GameState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.draw(mTableSprite);
	window.draw(mNextBlockSprite);
	window.draw(mGUISprite);
	size_t i = 0;
	size_t j = 0;
	//Draw fixed blocks
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (mTable[i][j])
			{
				mBlockSprite.setTextureRect(sf::IntRect((mTable[i][j] - 1) * blockSize, 0, blockSize, blockSize));
				mBlockSprite.setPosition(j * blockSize, i * blockSize);
				mBlockSprite.move(10, 15);//Adjusting offset causing by margin
				window.draw(mBlockSprite);
			}
		}
	}
	//Draw dropping Blocks
	mBlockSprite.setTextureRect(sf::IntRect((currentBlockID - 1) * blockSize, 0, blockSize, blockSize));
	for (i = 0; i < 4; i++)
	{
		mBlockSprite.setPosition(currentBlockPos[i].x * blockSize, currentBlockPos[i].y * blockSize);
		mBlockSprite.move(10, 15);//Adjusting offset causing by margin
		window.draw(mBlockSprite);
	}

	//Display the final position of the block after it has fallen
	sf::Vector2u blockPos[4] = {currentBlockPos[0],currentBlockPos[1] ,currentBlockPos[2], currentBlockPos[3] };
	sf::Vector2u beforeblockPos[4];
	while (checkblock(blockPos) == true)
	{
		for (int i = 0; i < 4; i++)
		{
			beforeblockPos[i] = blockPos[i];
			++blockPos[i].y;
		}
	}
	//illegal pos
	for (int i = 0; i < 4; i++)
		blockPos[i] = beforeblockPos[i];

	sf::Color color = mBlockSprite.getColor();
	color.a = 96; // set half-transparent
	mBlockSprite.setColor(color);

	for (i = 0; i < 4; i++)
	{
		mBlockSprite.setPosition(blockPos[i].x * blockSize, blockPos[i].y * blockSize);
		mBlockSprite.move(10, 15);//Adjusting offset causing by margin
		window.draw(mBlockSprite);
	}

	color.a = 255; // reset not transparent
	mBlockSprite.setColor(color);

	//Draw next block in nextblock area
	if (initNextBlockID) {
		mBlockSprite.setTextureRect(sf::IntRect((nextBlockID - 1) * blockSize, 0, blockSize, blockSize));
		for (i = 0; i < 4; i++)
		{
			mBlockSprite.setPosition((Blocks::blocks[nextBlockID - 1][i]) % 2 * blockSize + width * blockSize + margin + 33 - (nextBlockID == Blocks::Hero) * 15, (Blocks::blocks[nextBlockID - 1][i]) / 2 * blockSize + 5 + (nextBlockID == Blocks::Hero) * 16);
			window.draw(mBlockSprite);
		}
	}



	//Draw data panal
	window.draw(mCurrentScoreText);
	window.draw(mCurrentScoreNumText);
	window.draw(mBestScoreText);
	window.draw(mBestScoreNumText);
	window.draw(mMagicSprite);
	window.draw(mMagicText);
	window.draw(mMagicNumText);
	if (comboDispaly) {
		comboTimer += comboClock.restart();
		if (comboTimer >= sf::seconds(2)) {
			comboDispaly = false;
		}
		window.draw(mComboText);
	}

};



bool GameState::checkblock(sf::Vector2u blockPos[4]) const {
	for (int i = 0; i < 4; i++)
	{
		if (blockPos[i].x > width - 1 ||
			blockPos[i].y > height - 1 ||
			blockPos[i].x < 0 ||
			mTable[blockPos[i].y][blockPos[i].x] != 0)
		{
			return false;
		}
	}
	return true;
}


void GameState::blockmove(sf::Vector2u move) {
	for (int i = 0; i < 4; i++)
	{
		beforeBlockPos[i] = currentBlockPos[i];
		currentBlockPos[i].x += move.x;
		currentBlockPos[i].y += move.y;
	}

	if (checkblock(currentBlockPos) == false)
	{
		for (int i = 0; i < 4; i++)
		{
			currentBlockPos[i] = beforeBlockPos[i];
		}
	}
}

void GameState::spin() {
	if (currentBlockID == Blocks::Smashboy)//Square Shape
	{
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		beforeBlockPos[i] = currentBlockPos[i];
	}
	sf::Vector2u center = currentBlockPos[1];

	for (int i = 0; i < 4; i++)
	{
		sf::Vector2u tmp = currentBlockPos[i];
		currentBlockPos[i].x = center.x - tmp.y + center.y;
		currentBlockPos[i].y = tmp.x - center.x + center.y;
	}
	if (checkblock(currentBlockPos) == false)
	{
		for (int i = 0; i < 4; i++)
		{
			currentBlockPos[i] = beforeBlockPos[i];
		}
	}

}

void GameState::dropBotton()
{
	mSound.play(SoundEffect::Drop);
	while (checkblock(currentBlockPos) == true)
	{
		for (int i = 0; i < 4; i++)
		{
			beforeBlockPos[i] = currentBlockPos[i];
			++currentBlockPos[i].y;
		}
	}

	//Illegal Pos
	for (int i = 0; i < 4; i++)
	{
		currentBlockPos[i] = beforeBlockPos[i];

	}

	if (initNextBlockID == false)
	{
		nextBlockID = Blocks::ID(1 + rand() % 7);
		initNextBlockID = true;
	}

	for (int i = 0; i < 4; i++){
		currentBlockPos[i] = beforeBlockPos[i];
		mTable[currentBlockPos[i].y][currentBlockPos[i].x] = currentBlockID;
	}

	newblock();
	nextBlockID = Blocks::ID(1 + rand() % 7);

}

void GameState::drop()
{
	for (int i = 0; i < 4; i++)
	{
		beforeBlockPos[i] = currentBlockPos[i];
		++currentBlockPos[i].y;
	}

	if (initNextBlockID == false)
	{
		nextBlockID = Blocks::ID(1 + rand() % 7);
		initNextBlockID = true;
	}

	if (checkblock(currentBlockPos) == false)
	{
		for (int i = 0; i < 4; i++)
		{
			currentBlockPos[i] = beforeBlockPos[i];
			mTable[currentBlockPos[i].y][currentBlockPos[i].x] = currentBlockID;
		}
		initNextBlockID = false;
		newblock();
	}
}

void GameState::pushMagicState() {
	if (magic > 0) {
		requestStackPush(States::Magic);
		useMagic = true;
		magic--;
	}
}


void GameState::newblock()//create next block
{
	int i = nextBlockID - 1;
	int j = 0;
	for (j = 0; j < 4; j++)
	{
		currentBlockPos[j].x = (Blocks::blocks[i][j]) % 2+ width / 2 - 1;
		currentBlockPos[j].y = (Blocks::blocks[i][j]) / 2;
	}
	if (!checkFail())
	{
		for (j = 0; j < 4; j++)
		{
			currentBlockPos[j].x = beforeBlockPos[j].x;
			currentBlockPos[j].y = beforeBlockPos[j].y;
		}
		initNextBlockID = true;
		requestStackPush(States::GameOver);
		return;
	}
	currentBlockID = nextBlockID;
}

void GameState::copyData() {
	mSave->setCurrentBlockID(currentBlockID);
	mSave->setCurrentScore(currentScore);
	mSave->setNextBlockID(nextBlockID);
	mSave->setTable(mTable);
	mSave->setMagic(magic);
	return;
}

