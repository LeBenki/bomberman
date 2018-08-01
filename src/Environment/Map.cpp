/*
** EPITECH PROJECT, 2018
** Map
** File description:
** Implementation of Map
*/

#include <memory>
#include <TileGate.hpp>
#include "TileBonusSkull.hpp"
#include "TileBonusRangeMax.hpp"
#include "FallingBlock.hpp"
#include "TileEgg.hpp"
#include "TileBonusKick.hpp"
#include "TileBonusPassSoftWall.hpp"
#include "TileBonusBomb.hpp"
#include "TileBonusRange.hpp"
#include "Window.hpp"
#include "TileFire.hpp"
#include "TileBonusSpeed.hpp"
#include "Map.hpp"
#include "TileBonusRedBomb.hpp"
#include "TileBonusShield.hpp"

Map::Map(const std::vector<std::string> &mapContent, BiomeManager::Name biome,
         irr::s32 tileSize) : tileSize(tileSize) , bonusNumber(10), biome(biome), destructedX(1), destructedY(1), destroyDirection(0), destroyRound(1), destructedWalls(0)
{
	fillMapContent(mapContent);
}

Map& Map::operator<<(const std::vector<std::string> &content)
{
	tiles.clear();
	fillMapContent(content);
	return *this;
}

void Map::fillMapContent(const std::vector<std::string> &mapContent)
{
	int i = 0;

	for (auto const &line : mapContent) {
		tiles.emplace_back();
		for (auto const &c : line) {
			if (c == '#')
				tiles[i].push_back(std::make_unique<TileHardWall> (biome));
			else if (c == 'X')
				tiles[i].push_back(std::make_unique<TileSoftWall> (biome));
			else if (c == 'G')
				tiles[i].push_back(std::make_unique<TileGate> ());
			else if (c == ' ' || c == 'M')
				tiles[i].push_back(std::make_unique<TileEmpty> (biome));
		}
		++i;
	}
}

void Map::draw()
{
	for (irr::s32 y = 0; y < (irr::s32)tiles.size(); y++) {
		for (irr::s32 x = 0; x < (irr::s32)tiles[y].size(); x++) {
			tiles[y][x]->draw(x, y * -1, tileSize);
		}
	}
}

irr::u32 Map::getWidth() const
{
	if (!tiles[0].size())
		return (0);
	return tiles[0].size() * tileSize;
}

irr::u32 Map::getHeight() const
{
	if (!tiles.size())
		return (0);
	return tiles.size() * tileSize;
}

irr::u32 Map::getTileSize() const
{
	return tileSize;
}

const std::vector<std::vector<std::unique_ptr<ITile>>> &Map::getTiles() const
{
	return tiles;
}

std::vector<std::vector<std::unique_ptr<ITile>>> &Map::getTiles()
{
	return tiles;
}

bool Map::checkCollision(irr::f32 oldX, irr::f32 oldZ, irr::f32 x, irr::f32 z, bool canPassSoft, bool isBomb, int direction) const
{
	int newX = 0;
	int newY = 0;

	if (isBomb) {
		switch (direction) {
			case 3:
				newX = (int) (x / tileSize + 0.5);
				newY = (int) ((z + (tileSize / 2)) / tileSize * -1 + 0.5);
				break;
			case 4:
				newX = (int) (x / tileSize + 0.5);
				newY = (int) ((z - (tileSize / 2)) / tileSize * -1 + 0.5);
				break;
			case 2:
				newX = (int) ((x + (tileSize / 2)) / tileSize + 0.5);
				newY = (int) (z / tileSize * -1 + 0.5);
				break;
			case 1:
				newX = (int) ((x - (tileSize / 2)) / tileSize + 0.5);
				newY = (int) (z / tileSize * -1 + 0.5);
				break;
			default:
				break;
		}
	}
	else {
		newX = (int) (x / tileSize + 0.5);
		newY = (int) (z / tileSize * -1 + 0.5);
	}

	auto oldXi = (int)(oldX / tileSize + 0.5);
	auto oldYi = (int)(oldZ / tileSize * -1 + 0.5);

	if (newY != oldYi && newX != oldXi)
		return true;
	if (newX < 0 || newY < 0)
		return true;
	if (canPassSoft)
		return tiles[(newY)][(newX)]->getType() != ITile::GATE &&
			tiles[(newY)][(newX)]->getType() != ITile::EMPTY &&
			tiles[(newY)][(newX)]->getType() != ITile::FIRE &&
			tiles[(newY)][(newX)]->getType() != ITile::BONUS &&
			tiles[(newY)][(newX)]->getType() != ITile::SOFT_WALL;
	else
		return tiles[(newY)][(newX)]->getType() != ITile::GATE &&
			tiles[(newY)][(newX)]->getType() != ITile::EMPTY &&
			tiles[(newY)][(newX)]->getType() != ITile::FIRE &&
			tiles[(newY)][(newX)]->getType() != ITile::BONUS;
}

bool Map::checkFire(double x, double z) const
{
	auto tmpZ2 = (int)(x / tileSize + 0.5);
	auto tmpX2 = (int)(z / tileSize * -1 + 0.5);

	if (tmpZ2 < 0 || tmpX2 < 0)
		return true;
	return tiles[(tmpX2)][(tmpZ2)]->getType() == ITile::FIRE;
}

bool Map::checkDoor(double x, double z) const
{
	auto tmpZ2 = (int)(x / tileSize + 0.5);
	auto tmpX2 = (int)(z / tileSize * -1 + 0.5);

	if (tmpZ2 < 0 || tmpX2 < 0)
		return true;
	if (tiles[(tmpX2)][(tmpZ2)]->getType() == ITile::GATE) {
		TileGate *gate = (TileGate *)tiles[(tmpX2)][(tmpZ2)].get();
		return gate->isIsOpen();
	}
	return false;
}

std::vector<std::string> Map::getMapInLuaFormat() const
{
	std::vector<std::string> luaMap;
	int count = 0;

	for (auto &i: tiles) {
		luaMap.emplace_back();
		for (auto &j : i) {
			luaMap[count].push_back(j->getLuaCharacter());
		}
		++count;
	}
	return luaMap;
}

void Map::breakSoftWallAndBonus(size_t x, size_t y)
{
	bool isSoft;

	if (tiles[y][x]->getType() == ITile::SOFT_WALL ||
		tiles[y][x]->getType() == ITile::BONUS)
	{
		isSoft = tiles[y][x]->getType() == ITile::SOFT_WALL;
		auto ptr = tiles[y][x].release();
		delete ptr;
		double newY = y;
		tiles[y][x] = std::make_unique<TileFire>(biome, x * tileSize, newY * tileSize * - 1, isSoft);
		tiles[y][x]->draw(x, y * -1, tileSize);
	}
}

size_t Map::getNbOfVerticalTiles() const
{
	return tiles.size();
}

size_t Map::getNbOfHorizontalTiles() const
{
	return tiles[0].size();
}

void Map::fireOnEmpty(size_t x, size_t y)
{
	if (tiles[y][x]->getType() == ITile::EMPTY)
	{
		auto ptr = tiles[y][x].release();
		delete ptr;
		double newY = y;
		tiles[y][x] = std::make_unique<TileFire>(biome, x * tileSize, newY * tileSize * -1, false);
		tiles[y][x]->draw(x, y * -1, tileSize);
	}
}

void Map::refreshFire()
{
	for (size_t y = 0; y < getNbOfVerticalTiles(); ++y) {
		for (size_t x = 0; x < getNbOfHorizontalTiles(); ++x) {
			if (tiles[y][x]->getType() == ITile::FIRE) {
				TileFire *fire = (TileFire *)(tiles[y][x].get());
				if (fire->isFinish()) {
					if (fire->isSoft()) {
						generateBonus(x, y);
					}
					else {
						auto ptr = tiles[y][x].release();
						delete ptr;
						tiles[y][x] = std::make_unique<TileEmpty> (biome);
					}
					tiles[y][x]->draw(x, y * -1, tileSize);
				}
			}
		}
	}
}

void Map::refresh()
{
	refreshFire();
	refreshBonus();
}

void Map::refreshBonus()
{
	for (size_t y = 0; y < getNbOfVerticalTiles(); ++y) {
		for (size_t x = 0; x < getNbOfHorizontalTiles(); ++x) {
			if (tiles[y][x]->getType() == ITile::BONUS) {
				ABonusTile *bonus = (ABonusTile *)(tiles[y][x].get());
				bonus->refresh();
			}
		}
	}
}
void Map::checkBonus(Bomberman &bomberman, double x,
		     double z)
{
	auto tmpZ2 = (int)(x / tileSize + 0.5);
	auto tmpX2 = (int)(z / tileSize * -1 + 0.5);

	if (tmpZ2 < 0 || tmpX2 < 0)
		return;
	if (tiles[(tmpX2)][(tmpZ2)]->getType() != ITile::BONUS)
		return;
	ABonusTile *bonus = (ABonusTile *)(tiles[(tmpX2)][(tmpZ2)].get());
	bonus->buffBomberman(bomberman);
	auto ptr = tiles[(tmpX2)][(tmpZ2)].release();
	delete ptr;
	tiles[(tmpX2)][(tmpZ2)] = std::make_unique<TileEmpty> (biome);
	tiles[(tmpX2)][(tmpZ2)]->draw(tmpZ2, tmpX2 * -1, tileSize);
}

void Map::generateBonus(size_t x, size_t y)
{
	auto ptr = tiles[y][x].release();
	delete ptr;
	if (generateRandomNumber(10) > 4)
		tiles[y][x] = std::make_unique<TileEmpty> (biome);
	else
	{
		size_t num = generateRandomNumber(10);
		if (num > 7) {
			switch (generateRandomNumber(7)) {
				case 1:
					tiles[y][x] = std::make_unique<TileBonusPassSoftWall> (biome);
					break;
				case 2:
					tiles[y][x] = std::make_unique<TileBonusKick> (biome);
					break;
				case 3:
					tiles[y][x] = std::make_unique<TileBonusRedBomb> (biome);
					break;
				case 4:
					tiles[y][x] = std::make_unique<TileBonusShield> (biome);
					break;
				case 5:
					tiles[y][x] = std::make_unique<TileEgg> (biome);
					break;
				case 6:
					tiles[y][x] = std::make_unique<TileBonusSkull> (biome);
					break;
				case 7:
					tiles[y][x] = std::make_unique<TileBonusRangeMax> (biome);
					break;
				default:
					throw std::invalid_argument("Bonus problem");
			}
		}
		else {
			switch (generateRandomNumber(3))
			{
				case 1:
					tiles[y][x] = std::make_unique<TileBonusSpeed>(biome);
					break;
				case 2:
					tiles[y][x] = std::make_unique<TileBonusBomb>(biome);
					break;
				case 3:
					tiles[y][x] = std::make_unique<TileBonusRange>(biome);
					break;
				default:
					throw std::invalid_argument("Bonus problem");
			}
		}
	}
}

size_t Map::generateRandomNumber(size_t max)
{
	std::mt19937 rng;

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type>
		distribution(1, max);
	return distribution(rng);
}

std::ostream &operator<<(std::ostream &stream, ITile &tile)
{
	stream << tile.getLuaCharacter();
	return stream;
}

BiomeManager::Name Map::getBiome() const
{
    return biome;
}

void Map::setBiome(BiomeManager::Name newBiome)
{
    biome = newBiome;
}

void Map::startDestruction(std::vector<AEntity *> &entities)
{
	bool created = false;

	destructedX %= tiles[0].size();
	destructedY %= tiles.size();
	if (tiles[destructedY][destructedX]->getType() != ITile::HARD_WALL) {
		irr::core::vector3df pos = {(irr::f32)destructedX * tileSize, 100, (irr::f32)((irr::f32)destructedY * -1 * tileSize)};
		fallingBlocks.push_back(new FallingBlock(biome, pos, tileSize, destructedX, destructedY));
		created = true;
	}
	if (destroyDirection == 0)
		++destructedX;
	else if (destroyDirection == 1)
		--destructedX;
	else if (destroyDirection == 2)
		++destructedY;
	else if (destroyDirection == 3)
		--destructedY;

	if (destroyDirection == 0 && destructedX == (tiles[0].size() - 1 - destroyRound))
		destroyDirection = 2;
	else if (destroyDirection == 1 && destructedX == destroyRound)
		destroyDirection = 3;
	else if (destroyDirection == 2 && destructedY == (tiles.size() - 1 - destroyRound))
		destroyDirection = 1;
	else if (destroyDirection == 3 && destructedY == destroyRound) {
		destroyDirection = 0;
		++destructedY;
		++destructedX;
		++destroyRound;
	}
	if (!created)
	{
		++destructedWalls;
		return startDestruction(entities);
	}
}

bool Map::canDestroy()
{
	static size_t i = 0;

	return (++i + destructedWalls < (((tiles[0].size() - 2) * (tiles.size() - 2))));
}

void Map::refreshBlocks(std::vector<AEntity *> entities)
{
	auto size = static_cast<int>(fallingBlocks.size());
	for (int i = 0; i < size; ++i) {
		fallingBlocks[i]->down(*this, entities);
		if (fallingBlocks[i]->isIsDown()) {
			delete fallingBlocks[i];
			fallingBlocks.erase(fallingBlocks.begin() + i);
			refreshBlocks(entities);
			break;
		}
	}
}

void Map::setTileSize(irr::s32 tileSize)
{
	Map::tileSize = tileSize;
}

void Map::clearFallingBlocks()
{
	unsigned long size = fallingBlocks.size();

	for (unsigned long i = 0; i < size; ++i) {
		delete fallingBlocks[i];
		fallingBlocks.erase(fallingBlocks.begin() + i);
		clearFallingBlocks();
		break;
	}
}