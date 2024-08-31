#pragma once
#include <StateIdentifiers.h>
#include <ResourceIdentifiers.h>
#include <SoundPlayer.h>
#include <MusicPlayer.h>
#include <Accounts.h>
#include <Saves.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
namespace sf
{
	class RenderWindow;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds,ImageHolder& image);

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		ImageHolder*		image;
		Accounts::Ptr		mAccount;
		Saves::Ptr			mSave;
		MusicPlayer*		music;
		SoundPlayer*		sounds;

	};

public:
						State(StateStack& stack, Context &context);
	virtual				~State();

	virtual void		draw()=0;
	virtual bool		update() = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;

private:
	StateStack*			mStack;
	Context				mContext;
};