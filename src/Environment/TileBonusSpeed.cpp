/*
** EPITECH PROJECT, 2018
** TileBonusSpeed
** File description:
** Implementation of TileBonusSpeed
*/

#include "TileBonusSpeed.hpp"

TileBonusSpeed::TileBonusSpeed(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSSPEED, biome, type, 'B')
{

}

TileBonusSpeed::~TileBonusSpeed()
{

}

void TileBonusSpeed::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("SpeedUp");
	bomberman.speedUp();
}
