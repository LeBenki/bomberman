/*
** EPITECH PROJECT, 2018
** TileBonusShield
** File description:
** Implementation of TileBonusShield
*/

#include <Bomberman.hpp>
#include "TileBonusShield.hpp"

TileBonusShield::TileBonusShield(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSSHIELD, biome, type, 'B')
{

}

void TileBonusShield::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("Shield");
	bomberman.setShield();
}

TileBonusShield::~TileBonusShield()
{

}