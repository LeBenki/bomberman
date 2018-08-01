/*
** EPITECH PROJECT, 2018
** TileHardWall
** File description:
** Implementation of TileHardWall
*/

#include "TileHardWall.hpp"

TileHardWall::TileHardWall(BiomeManager::Name biome, Type type)
	: ABiomeTile(biome, type, '#')
{
}

TileHardWall::~TileHardWall()
= default;
