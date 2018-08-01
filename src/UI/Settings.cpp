/*
** EPITECH PROJECT, 2018
** Settings
** File description:
** Implementation of Settings
*/

#include <Lang.hpp>
#include <ResourceManager.hpp>
#include "Settings.hpp"

std::vector<irr::core::dimension2d<irr::u32>> Settings::resolutions = {
	{1920, 1080},
	{1600, 900},
	{1366, 768},
	{1200, 700},
	{800, 600}
};

Settings::Settings() : resolutionId(0), fullscreen(true), quality(ULTRA),
		shadows(false), musicVolume(100), fxVolume(100), splitScreen(false), language(ENGLISH), particles(true)
{
	load();
	resolutions = {
		{1920, 1080},
		{1600, 900},
		{1366, 768},
		{1200, 700},
		{800, 600}
	};
	resolution = resolutions[resolutionId];
	Lang::loadTexts();
}

void Settings::save()
{
	std::ofstream myfile(ResourceManager::getConfigPath(), std::fstream::in
						  | std::fstream::out | std::fstream::trunc);

	if (!myfile.is_open())
		return;
	myfile << "[window]" << std::endl;
	myfile << "resolution=" << getResolutionId() << std::endl;
	myfile << "fullscreen=" << isFullscreen() << std::endl << std::endl;

	myfile << "[graphics]" << std::endl;
	myfile << "quality=" << getQuality() << std::endl;
	myfile << "shadows=" << isShadows() << std::endl;
	myfile << "particles=" << isParticles() << std::endl << std::endl;

	myfile << "[audio]" << std::endl;
	myfile << "music=" << getMusicVolume() << std::endl;
	myfile << "fx=" << getFxVolume() << std::endl << std::endl;

	myfile << "[misc]" << std::endl;
	myfile << "split_screen=" << isSplitScreen() << std::endl;
	myfile << "language=" << getLanguage() << std::endl;

	myfile.close();
}

static inline std::vector<std::string> split(const std::string &text, char sep)
{
	std::vector<std::string> tokens;
	std::size_t start = 0;
	std::size_t end = 0;

	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

void Settings::load()
{
	std::ifstream input(ResourceManager::getConfigPath());

	if (!input.is_open())
		return;
	for (std::string line; getline(input, line); )
	{
		std::vector<std::string> lines = split(line, '=');
		if (lines.size() != 2)
			continue;

		if (lines[0] == "fullscreen")
			setFullscreen((bool) atoi(lines[1].c_str()));
		else if (lines[0] == "quality")
			setQuality((Settings::Graphics)atoi(lines[1].c_str()));
		else if (lines[0] == "shadows")
			setShadows((bool)atoi(lines[1].c_str()));
		else if (lines[0] == "music")
			setMusicVolume(atoi(lines[1].c_str()));
		else if (lines[0] == "fx")
			setFxVolume(atoi(lines[1].c_str()));
		else if (lines[0] == "split_screen")
			setSplitScreen((bool)atoi(lines[1].c_str()));
		else if (lines[0] == "split_screen")
			setSplitScreen((bool)atoi(lines[1].c_str()));
		else if (lines[0] == "language")
			setLanguage((Settings::Language)atoi(lines[1].c_str()));
		else if (lines[0] == "resolution")
			setResolutionId(atoi(lines[1].c_str()));
		else if (lines[0] == "particles")
			setParticles(atoi(lines[1].c_str()));
	}
}

irr::core::dimension2d<irr::u32> Settings::getResolution() const
{
	return resolution;
}

bool Settings::isFullscreen() const
{
	return fullscreen;
}

void Settings::setFullscreen(bool fullscreen)
{
	Settings::fullscreen = fullscreen;
}

void Settings::setResolution(const irr::core::dimension2d<irr::u32> &resolution)
{
	Settings::resolution = resolution;
}

int Settings::getResolutionId() const
{
	return resolutionId;
}

void Settings::setResolutionId(int resolutionId)
{
	Settings::resolutionId = resolutionId;
}

Settings::Graphics Settings::getQuality() const
{
	return quality;
}

void Settings::setQuality(Settings::Graphics quality)
{
	Settings::quality = quality;
}

bool Settings::isShadows() const
{
	return shadows;
}

void Settings::setShadows(bool shadows)
{
	Settings::shadows = shadows;
}

int Settings::getMusicVolume() const
{
	return musicVolume;
}

void Settings::setMusicVolume(int musicVolume)
{
	Settings::musicVolume = musicVolume;
}

int Settings::getFxVolume() const
{
	return fxVolume;
}

void Settings::setFxVolume(int fxVolume)
{
	Settings::fxVolume = fxVolume;
}

bool Settings::isSplitScreen() const
{
	return splitScreen;
}

void Settings::setSplitScreen(bool splitScreen)
{
	Settings::splitScreen = splitScreen;
}

Settings::~Settings()
{
	save();
}

Settings::Language Settings::getLanguage() const
{
	return language;
}

void Settings::setLanguage(Settings::Language language)
{
	this->language = language;
}

bool Settings::isParticles() const
{
	return particles;
}

void Settings::setParticles(bool particles)
{
	Settings::particles = particles;
}
