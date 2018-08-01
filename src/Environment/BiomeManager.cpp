/*
** EPITECH PROJECT, 2018
** BiomeManager
** File description:
** Implementation of BiomeManager
*/

#include <Window.hpp>
#include "BiomeManager.hpp"

std::map<BiomeManager::Name, std::map<BiomeManager::Type, std::string>> BiomeManager::paths = {
	{BEACH, {
		{HardWallModel, "/Levels/Beach/Shell/"},
		{SoftWallModel, "/Levels/Beach/Ball/"},
		{HardWallTexture, "/Levels/Beach/Shell/"},
		{SoftWallTexture, "/Levels/Beach/Ball/"},
		{FloorTexture, "/Levels/Beach/Floors/"}
	}},
	{JUNGLE, {
		 {HardWallModel, "/Levels/Jungle/Boulder/"},
		 {SoftWallModel, "/Levels/Jungle/Barrel/"},
		 {HardWallTexture, "/Levels/Jungle/Boulder/"},
		 {SoftWallTexture, "/Levels/Jungle/Barrel/"},
		 {FloorTexture, "/Levels/Jungle/Floors/"}
	}},
	{FACTORY, {
		 {HardWallModel, "/Levels/Factory/Wall/"},
		 {SoftWallModel, "/Levels/Factory/Box/"},
		 {HardWallTexture, "/Levels/Factory/Wall/"},
		 {SoftWallTexture, "/Levels/Factory/Box/"},
		 {FloorTexture, "/Levels/Factory/Floors/"}
	}},
	{VOLCANO, {
		{HardWallModel, "/Levels/Volcano/Crystal/"},
		{SoftWallModel, "/Levels/Volcano/Rock/"},
		{HardWallTexture, "/Levels/Volcano/Crystal/"},
		{SoftWallTexture, "/Levels/Volcano/Rock/"},
		{FloorTexture, "/Levels/Volcano/Floors/"}
		}},
	{ICE, {
		{HardWallModel, "/Levels/Ice/Ice/"},
		{SoftWallModel, "/Levels/Ice/Snowman/"},
		{HardWallTexture, "/Levels/Ice/Ice/"},
		{SoftWallTexture, "/Levels/Ice/Snowman/"},
		{FloorTexture, "/Levels/Ice/Floors/"}
	}},
	{RETRO, {
		{HardWallModel, "/Levels/Retro/Cube/"},
		{SoftWallModel, "/Levels/Retro/NES/"},
		{HardWallTexture, "/Levels/Retro/Cube/"},
		{SoftWallTexture, "/Levels/Retro/NES/"},
		{FloorTexture, "/Levels/Retro/Floors/"}
	      }},
	{CITY, {
		{HardWallModel, "/Levels/City/Tower/"},
		{SoftWallModel, "/Levels/City/Bin/"},
		{HardWallTexture, "/Levels/City/Tower/"},
		{SoftWallTexture, "/Levels/City/Bin/"},
		{FloorTexture, "/Levels/City/Floors/"}
		}},
	{MUSHROOM, {
		{HardWallModel, "/Levels/Mushroom/Stone/"},
		{SoftWallModel, "/Levels/Mushroom/Block/"},
		{HardWallTexture, "/Levels/Mushroom/Stone/"},
		{SoftWallTexture, "/Levels/Mushroom/Block/"},
		{FloorTexture, "/Levels/Mushroom/Floors/"}
	       }}
};

const std::string BiomeManager::getPathFromNameAndType(Name name, Type type)
{
	switch (Window::settings.getQuality()) {
		case Settings::LOW:
			return ResourceManager::prefixPath + paths[name][type] + "low" + (type == HardWallModel || type == SoftWallModel ? ".obj" : ".png");
		case Settings::MEDIUM:
			return ResourceManager::prefixPath + paths[name][type] + "medium" + (type == HardWallModel || type == SoftWallModel ? ".obj" : ".png");
		case Settings::ULTRA:
			return ResourceManager::prefixPath + paths[name][type] + "high" + (type == HardWallModel || type == SoftWallModel ? ".obj" : ".png");
	}
	return "";
}

BiomeManager::Name BiomeManager::getRandomBiome(int a, int b)
{
	std::mt19937 rng;

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type>
		distribution(a, b);
	auto index = distribution(rng);
	return BiomeManager::Name(index);
}