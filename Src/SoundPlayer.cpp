#include <SoundPlayer.h>

#include <SFML/Audio/Listener.hpp>

SoundPlayer::SoundPlayer()
	: mSoundBuffers()
	, mSounds()
	, isMute(0)
{
	mSoundBuffers.load(SoundEffect::Button, "Media/Sound/Button.wav");
	mSoundBuffers.load(SoundEffect::Drop, "Media/Sound/Drop.wav");
	mSoundBuffers.load(SoundEffect::LineClear, "Media/Sound/LineClear.wav");
	mSoundBuffers.load(SoundEffect::Combo, "Media/Sound/Combo.wav");
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	if (isMute)return;
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	sf::Sound& sound = mSounds.back();
	sound.play();
}


void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

bool SoundPlayer::getMute() const{
	return isMute;
}

void SoundPlayer::setMute() {
	isMute = !isMute;
}

