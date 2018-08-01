/*
** EPITECH PROJECT, 2018
** TileEmpty
** File description:
** Declaration of TileEmpty
*/

#ifndef INDIE_STUDIO_TILEEMPTY_HPP
	#define INDIE_STUDIO_TILEEMPTY_HPP

#include "ATile.hpp"
#include "BiomeManager.hpp"

class TileEmpty : public ATile
{
public:
	explicit TileEmpty(BiomeManager::Name biome, Type type = EMPTY);
	~TileEmpty() override;
};

#endif //INDIE_STUDIO_TILEEMPTY_HPP
