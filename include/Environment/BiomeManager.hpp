/*
** EPITECH PROJECT, 2018
** BiomeManager
** File description:
** Declaration of BiomeManager
*/

#ifndef INDIE_STUDIO_BIOMEMANAGER_HPP
	#define INDIE_STUDIO_BIOMEMANAGER_HPP

#include <map>
#include <string>

class BiomeManager
{
public:
	BiomeManager() = delete;
	enum Name {
		RANDOM = 0,
		BEACH,
		JUNGLE,
		FACTORY,
		VOLCANO,
		ICE,
		RETRO,
		CITY,
		MUSHROOM
	};
	enum Type {
		HardWallModel,
		SoftWallModel,
		HardWallTexture,
		SoftWallTexture,
		FloorTexture
	};
	static std::map<Name, std::map<Type, std::string>> paths;
	static const std::string getPathFromNameAndType(Name name, Type type);
	static BiomeManager::Name getRandomBiome(int, int);
};

#endif //INDIE_STUDIO_BIOMEMANAGER_HPP
