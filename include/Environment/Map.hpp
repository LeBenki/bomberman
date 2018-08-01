/*
** EPITECH PROJECT, 2018
** Map
** File description:
** Declaration of Map
*/

#ifndef CPP_INDIE_STUDIO_MAP_HPP
	#define CPP_INDIE_STUDIO_MAP_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <irrlicht/irrlicht.h>
#include "TileHardWall.hpp"
#include "TileSoftWall.hpp"
#include "TileEmpty.hpp"
#include "TileGate.hpp"

class Bomberman;
class AEntity;
class FallingBlock;

class Map
{
public:
	Map() = default;
	Map(const std::vector<std::string> &mapContent, BiomeManager::Name biome, irr::s32 tileSize = 20);
	Map& operator<<(const std::vector<std::string> &content);
	void refreshFire();
	void refresh();
	void refreshBonus();
	void draw();
	irr::u32 getWidth() const;
	irr::u32 getHeight() const;
	irr::u32 getTileSize() const;
	void fillMapContent(const std::vector<std::string> &mapContent);
	const std::vector<std::vector<std::unique_ptr<ITile>>> &getTiles() const;
	bool
	checkCollision(irr::f32 x, irr::f32 z, irr::f32 d, irr::f32 d1, bool, bool = false, int = 0) const;
	bool checkFire(double x, double z) const;
	void checkBonus(Bomberman &bomberman, double x, double z);
	void generateBonus(size_t x, size_t y);
	std::vector<std::string> getMapInLuaFormat() const;
	void breakSoftWallAndBonus(size_t x, size_t y);
	void fireOnEmpty(size_t x, size_t y);
	size_t getNbOfVerticalTiles() const;
	size_t getNbOfHorizontalTiles() const;
	size_t generateRandomNumber(size_t max);
	BiomeManager::Name getBiome() const;
	void setBiome(BiomeManager::Name newBiome);
	void startDestruction(std::vector<AEntity *> &entities);
	bool canDestroy();
	void refreshBlocks(std::vector<AEntity *> entities);
	std::vector<std::vector<std::unique_ptr<ITile>>> &getTiles();
	bool checkDoor(double x, double z) const;
	void setTileSize(irr::s32 tileSize);
	void clearFallingBlocks();
private:
	std::vector<std::vector<std::unique_ptr<ITile>>> tiles;
	irr::s32 tileSize;
	size_t bonusNumber;
	BiomeManager::Name biome;
	size_t destructedX;
	size_t destructedY;
	int destroyDirection;
	size_t destroyRound;
	std::vector<FallingBlock *> fallingBlocks;
	int destructedWalls;
};

std::ostream &operator<<(std::ostream& stream, ITile &tile);

#endif //CPP_INDIE_STUDIO_MAP_HPP
