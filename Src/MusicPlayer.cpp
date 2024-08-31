#include <MusicPlayer.h>


MusicPlayer::MusicPlayer()
	: mMusic()
	, mFilenames()
	, mVolume(100.f)
	, isMute(0)
	,currentMusic(Music::MirrorOfEdge)
{
	mFilenames[Music::MirrorOfEdge] = "Media/Music/Solar-Fields-Introduction.ogg";
	mFilenames[Music::TrackInTime] = "Media/Music/Dennis-Kuo-Track-in-Time.ogg";
	mFilenames[Music::Distance] = "Media/Music/Distance.ogg";
}

void MusicPlayer::play(Music::ID musicName)
{
	std::string filename = mFilenames[musicName];
	isMute = 0;
	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
	currentMusic = musicName;
}

void MusicPlayer::stop()
{
	mMusic.stop();
	isMute = 1;
}

void MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused) {
		mMusic.pause();
		isMute = 1;
	}
	else {
		mMusic.play();
		isMute = 0;
	}
}

bool MusicPlayer::getMute() {
	return isMute;
}

void MusicPlayer::setCurrentMusic(Music::ID id) {
	currentMusic = id;
}


Music::ID MusicPlayer::getCurrentMusic() {
	return currentMusic;
}



