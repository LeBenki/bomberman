/*
** EPITECH PROJECT, 2018
** TileSoftWall
** File description:
** TileSoftWall class definition
*/

#ifndef INDIE_STUDIO_TILE_SOFT_WALL_HPP
#define INDIE_STUDIO_TILE_SOFT_WALL_HPP

#include "ABiomeTile.hpp"

class TileSoftWall : public ABiomeTile
{
public:
	explicit TileSoftWall(BiomeManager::Name biome, Type type = SOFT_WALL);
	~TileSoftWall() override;

private:

};

#endif //INDIE_STUDIO_TILE_SOFT_WALL_HPP
