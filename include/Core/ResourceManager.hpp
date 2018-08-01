/*
** EPITECH PROJECT, 2018
** ResourceManager
** File description:
** Declaration of ResourceManager
*/

#ifndef INDIE_STUDIO_TEXTUREMANAGER_HPP
	#define INDIE_STUDIO_TEXTUREMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <Settings.hpp>

#include "BiomeManager.hpp"

class ResourceManager
{
public:
	enum Type {
		MODEL,
		TEXTURE
	};
	enum Name {
		BOMBERMAN1 = 1,
		BOMBERMAN2,
		BOMBERMAN3,
		BOMBERMAN4,
		BOMB,
		REDBOMB,
		FIRE,
		BEACHMOB,
		JUNGLEMOB,
		FACTORYMOB,
		VOLCANOMOB,
		ICEMOB,
		RETROMOB,
		CITYMOB,
		MUSHROOMMOB,
		MOUNT,
		BONUSSPEED,
		BONUSSKULL,
		BONUSRANGE,
		BONUSBOMB,
		BONUSEGG,
		BONUSSHIELD,
		BONUSREDBOMB,
		BONUSPASSSOFT,
		BONUSKICK,
		BONUSRANGEMAX,
		PARTICLES_FIRE,
		PARTICLES_SMOKE,
		PARTICLES_SHIELD,
		TIMER_HUD,
		MENU_LOADING,
		MENU_FONT,
		MENU_BACKGROUND,
		MENU_BUTTON,
		MENU_BUTTON_PRESSED,
		MENU_MAIN_BACKGROUND,
		AI_MOB,
		AI_BOMBERMAN,
		GATEOPEN,
		GATECLOSE,
		WIN,
		LOSE,
		DRAW
	};
	static const std::string getRes(Type type, Name name);
	static const std::string getResIcon(Name name);
	static const std::string getPlayerIcon(int id);
	static const std::string getMusicByBiome(BiomeManager::Name biome);
	static const ResourceManager::Name &getEnnemyByBiome(BiomeManager::Name biome);
	static const std::string getConfigPath();
	static const std::string getLangPath();
	static const std::string getSavePath();
	static const std::string getMenuPath(Name name);
	static const std::string getAiPath(Name name);
	static const std::string getMessagePath(Name name, Settings::Language lang);
	static std::map<std::string, std::string> soundPaths;
	static const std::string prefixPath;
private:
	static std::map<Name, std::pair<std::string, std::string>> paths;
	static std::map<Name, std::string> menuPaths;
	static std::map<Name, std::string> aiPaths;
	static std::map<Settings::Language, std::map<Name, std::string>> messagesPaths;
	static std::map<ResourceManager::Name, std::string> iconsPaths;
	static std::map<BiomeManager::Name, std::string> biomeMusics;
	static std::map<BiomeManager::Name, ResourceManager::Name> biomeEnnemies;
	static std::vector<std::string> playerIconsPaths;
	static const std::string configPath;
	static const std::string langPath;
	static const std::string savePath;
};

#endif //INDIE_STUDIO_TEXTUREMANAGER_HPP
