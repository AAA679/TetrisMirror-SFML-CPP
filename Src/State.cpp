#include <State.h>
#include <StateStack.h>

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds, ImageHolder& image)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, image(&image)
	, music(&music)
	, mAccount(std::make_shared<Accounts>())
	, sounds(&sounds)
	, mSave(std::make_shared<Saves>(10,20,1))
{
}

State::State(StateStack& stack, Context &context)
	: mStack(&stack)
	, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
