/*
** EPITECH PROJECT, 2018
** TileEgg
** File description:
** Implementation of TileEgg
*/

#include <Window.hpp>
#include "TileEgg.hpp"

TileEgg::TileEgg(BiomeManager::Name biome, ITile::Type type, char luaCharacter)
	: ABonusTile(ResourceManager::BONUSEGG, biome, type, luaCharacter)
{

}

void TileEgg::buffBomberman(Bomberman &bomberman)
{
	SoundEngine::playSound("Name");
	bomberman.setMount();
}

TileEgg::~TileEgg()
{

}
