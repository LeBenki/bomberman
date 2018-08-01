/*
** EPITECH PROJECT, 2018
** TileHardWall
** File description:
** Declaration of TileHardWall
*/

#ifndef INDIE_STUDIO_TILE_HARD_WALL_HPP
#define INDIE_STUDIO_TILE_HARD_WALL_HPP


#include "ABiomeTile.hpp"

class TileHardWall : public ABiomeTile
{
public:
	explicit TileHardWall(BiomeManager::Name biome, Type type = HARD_WALL);
	~TileHardWall() override;

private:

};


#endif //INDIE_STUDIO_TILE_HARD_WALL_HPP
