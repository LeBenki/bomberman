/*
** EPITECH PROJECT, 2018
** TileBonusBomb
** File description:
** Implementation of TileBonusBomb
*/

#include "TileBonusBomb.hpp"

TileBonusBomb::TileBonusBomb(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSBOMB, biome, type, 'B')
{

}

void TileBonusBomb::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("BombUp");
	bomberman.bombsUp();
}

TileBonusBomb::~TileBonusBomb()
{

}
