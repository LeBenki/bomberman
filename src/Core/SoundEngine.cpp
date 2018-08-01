/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Implementation of SoundEngine
*/

#include "SoundEngine.hpp"

irrklang::ISoundEngine *SoundEngine::soundEngine = irrklang::createIrrKlangDevice();
irrklang::ISound *SoundEngine::actualMusic;
float SoundEngine::musicVolume = 1;
float SoundEngine::effectVolume = 1;

bool SoundEngine::initSoundEngine()
{
	bool ret = true;

	try {
		if (!SoundEngine::soundEngine) {
			throw InitialisationFailed(
				"sound engine initialisation failed");
		}
		for (const auto &soundPair : ResourceManager::soundPaths) {
			auto sound = soundEngine->addSoundSourceFromFile(
				(ResourceManager::prefixPath + soundPair.second).c_str());
			soundEngine->addSoundSourceAlias(sound, soundPair.first.c_str());
		}
		SoundEngine::actualMusic = nullptr;
	} catch (const InitialisationFailed &e) {
		std::cerr << e.what() << std::endl;
		ret = false;
	}
	return ret;
}

void SoundEngine::playSound(const std::string &soundName)
{
	try {
		if (!SoundEngine::soundEngine)
			throw InitialisationFailed ("sound engine isn't initialised");
		auto sound = SoundEngine::soundEngine->play2D(soundName.c_str(),
			false, true);
		if (!sound)
			throw ResourceNotFound ("sound '" + soundName + "' not found");
		sound->setVolume(SoundEngine::effectVolume);
		sound->setIsPaused(false);
	} catch (const IndieExceptions &e) {
		std::cerr << e.what() << std::endl;
	}
}

void SoundEngine::playMusic(const std::string &musicName)
{
	try {
		if (!SoundEngine::soundEngine)
			throw InitialisationFailed ("sound engine isn't initialised");
		if (SoundEngine::actualMusic)
			SoundEngine::actualMusic->stop();
		SoundEngine::actualMusic =
			SoundEngine::soundEngine->play2D(musicName.c_str(),
			true, true);
		if (!SoundEngine::actualMusic)
			throw ResourceNotFound ("music '" + musicName + "' not found");
		SoundEngine::actualMusic->setVolume(SoundEngine::musicVolume);
		SoundEngine::actualMusic->setIsPaused(false);
	} catch (const IndieExceptions &e) {
		std::cerr << e.what() << std::endl;
	}
}

void SoundEngine::speedUpMusic()
{
	if (SoundEngine::actualMusic)
		SoundEngine::actualMusic->setPlaybackSpeed(1.5);
}

float SoundEngine::getMusicVolume()
{
	return musicVolume;
}

void SoundEngine::setMusicVolume(float volume)
{
	if (volume < 0 || volume > 1)
		throw std::out_of_range ("invalid range");
	musicVolume = volume;
	actualMusic->setIsPaused(true);
	actualMusic->setVolume(volume);
	actualMusic->setIsPaused(false);
}

float SoundEngine::getEffectVolume()
{
	return effectVolume;
}

void SoundEngine::setEffectVolume(float volume)
{
	if (volume < 0 || volume > 1)
		throw std::out_of_range ("invalid range");
	effectVolume = volume;
}
