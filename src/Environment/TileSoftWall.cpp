/*
** EPITECH PROJECT, 2018
** TileSoftWall
** File description:
** Implementation of TileSoftWall
*/

#include "TileSoftWall.hpp"

TileSoftWall::TileSoftWall(BiomeManager::Name biome, Type type)
	: ABiomeTile(biome, type, 'X')
{
}

TileSoftWall::~TileSoftWall()
= default;
