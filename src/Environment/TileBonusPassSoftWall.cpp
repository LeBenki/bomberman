/*
** EPITECH PROJECT, 2018
** TileBonusPassSoftWall
** File description:
** Implementation of TileBonusPassSoftWall
*/

#include <Bomberman.hpp>
#include "TileBonusPassSoftWall.hpp"

TileBonusPassSoftWall::TileBonusPassSoftWall(BiomeManager::Name biome, ITile::Type type)
	: ABonusTile(ResourceManager::BONUSPASSSOFT, biome, type, 'B')
{

}

void TileBonusPassSoftWall::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("TransIn");
	bomberman.passSoft();
}

TileBonusPassSoftWall::~TileBonusPassSoftWall()
{

}