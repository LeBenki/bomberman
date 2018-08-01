/*
** EPITECH PROJECT, 2018
** ATileBonusRedBomb
** File description:
** Implementation of ATileBonusRedBomb
*/

#include "TileBonusRedBomb.hpp"

TileBonusRedBomb::TileBonusRedBomb(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSREDBOMB, biome, type, 'B')
{

}

void TileBonusRedBomb::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("RedBomb");
	bomberman.setRedbomb();
}

TileBonusRedBomb::~TileBonusRedBomb()
{

}
