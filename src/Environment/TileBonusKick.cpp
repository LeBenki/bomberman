/*
** EPITECH PROJECT, 2018
** TileBonusKick
** File description:
** Implementation of TileBonusKick
*/

#include <Bomberman.hpp>
#include "TileBonusKick.hpp"

TileBonusKick::TileBonusKick(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSKICK, biome, type, 'B')
{

}

void TileBonusKick::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("Kick");
	bomberman.setCanKick();
}

TileBonusKick::~TileBonusKick()
{

}
