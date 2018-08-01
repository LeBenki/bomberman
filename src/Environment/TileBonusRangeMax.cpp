/*
** EPITECH PROJECT, 2018
** ABonusRangeMax
** File description:
** Implementation of ABonusRangeMax
*/

#include "TileBonusRangeMax.hpp"

TileBonusRangeMax::TileBonusRangeMax(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSRANGEMAX, biome, type, 'B')
{

}

void TileBonusRangeMax::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("FullFire");
	bomberman.rangeMax();
}

TileBonusRangeMax::~TileBonusRangeMax()
{

}