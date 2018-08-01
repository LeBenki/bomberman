/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Declaration of SoundEngine
*/

#ifndef INDIE_STUDIO_SOUNDENGINE_HPP
#define INDIE_STUDIO_SOUNDENGINE_HPP

#include <irrklang/irrKlang.h>
#include <iostream>
#include <sys/types.h>
#include <stdexcept>

#include "IndieExceptions.hpp"
#include "ResourceManager.hpp"

class SoundEngine {
	static irrklang::ISoundEngine *soundEngine;
	static irrklang::ISound *actualMusic;
	static float musicVolume;
	static float effectVolume;
public:
	static bool initSoundEngine();
	static void playSound(const std::string &soundName);
	static void playMusic(const std::string &musicName);
	static void speedUpMusic();
	static float getMusicVolume();
	static void setMusicVolume(float volume);
	static float getEffectVolume();
	static void setEffectVolume(float volume);
};

#endif //INDIE_STUDIO_SOUNDENGINE_HPP
