#pragma once
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <Utility.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
public:
								MusicPlayer();

	void						play(Music::ID theme);
	void						stop();

	void						setPaused(bool paused);
	void						setVolume(float volume);

	bool						getMute();

	void						setCurrentMusic(Music::ID id);
	Music::ID					getCurrentMusic();

private:
	Music::ID							currentMusic;
	sf::Music							mMusic;
	std::map<Music::ID, std::string>	mFilenames;
	float								mVolume;
	bool								isMute;
};
