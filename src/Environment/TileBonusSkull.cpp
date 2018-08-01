/*
** EPITECH PROJECT, 2018
** ABonusSkull
** File description:
** Implementation of ABonusSkull
*/

#include "TileBonusSkull.hpp"

TileBonusSkull::TileBonusSkull(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSSKULL, biome, type, 'C')
{

}

void TileBonusSkull::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("Skull");
	bomberman.setSkull();
}

TileBonusSkull::~TileBonusSkull()
{

}