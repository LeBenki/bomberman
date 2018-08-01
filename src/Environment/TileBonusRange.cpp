/*
** EPITECH PROJECT, 2018
** TileBonusRange
** File description:
** Implementation of TileBonusRange
*/

#include "TileBonusRange.hpp"

TileBonusRange::TileBonusRange(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSRANGE, biome, type, 'B')
{

}

void TileBonusRange::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("FireUp");
	bomberman.rangeUp();
}

TileBonusRange::~TileBonusRange()
{

}
