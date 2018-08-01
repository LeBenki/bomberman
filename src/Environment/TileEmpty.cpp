/*
** EPITECH PROJECT, 2018
** TileEmpty
** File description:
** Implementation of TileEmpty
*/

#include "TileEmpty.hpp"

TileEmpty::TileEmpty(BiomeManager::Name biome, Type type) : ATile(biome, type, ' ')
{
}

TileEmpty::~TileEmpty()
= default;
