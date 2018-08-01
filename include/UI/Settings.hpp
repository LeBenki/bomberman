/*
** EPITECH PROJECT, 2018
** Settings
** File description:
** Declaration of Settings
*/

#ifndef INDIE_STUDIO_SETTINGS_HPP
	#define INDIE_STUDIO_SETTINGS_HPP

#include <utility>
#include <vector>
#include <irrlicht/irrlicht.h>

class Settings
{
public:
	enum Graphics {
		LOW,
		MEDIUM,
		ULTRA
	};
	enum Language {
		NONE = 0,
		ENGLISH,
		FRENCH,
		SPANISH
	};
	Settings();
	void save();
	void load();
	irr::core::dimension2d<irr::u32> getResolution() const;
	bool isFullscreen() const;
	void setFullscreen(bool fullscreen);
	void setResolution(const irr::core::dimension2d<irr::u32> &resolution);
	int getResolutionId() const;
	void setResolutionId(int resolutionId);
	Graphics getQuality() const;
	void setQuality(Graphics quality);
	bool isShadows() const;
	void setShadows(bool shadows);
	int getMusicVolume() const;
	void setMusicVolume(int musicVolume);
	int getFxVolume() const;
	void setFxVolume(int fxVolume);
	static std::vector<irr::core::dimension2d<irr::u32>> resolutions;
	bool isSplitScreen() const;
	void setSplitScreen(bool splitScreen);
	Language getLanguage() const;
	void setLanguage(Language language);
	bool isParticles() const;
	void setParticles(bool particles);
	virtual ~Settings();

private:
	int resolutionId;
	irr::core::dimension2d<irr::u32> resolution;
	bool fullscreen;
	Graphics quality;
	bool shadows;
	int musicVolume;
	int fxVolume;
	bool splitScreen;
	Language language;
	bool particles;
};

#endif //INDIE_STUDIO_SETTINGS_HPP
