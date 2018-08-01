/*
** EPITECH PROJECT, 2018
** Mob
** File description:
** Implementation of Mob
*/

#include "Mob.hpp"

Mob::Mob(irr::core::vector3df &pos, int teamId, BiomeManager::Name biome)
		: AEntity(ResourceManager::getEnnemyByBiome(biome),
		          pos, teamId, Type::MOB),
		  _manager(ResourceManager::getAiPath(ResourceManager::AI_MOB))
{
}

Mob::~Mob()
{
}

void Mob::handleEvent(Map &map, std::vector<AEntity *> &entities)
{
	_manager.refresh(map, *this, entities);
	processActions(_manager.getEvents(), map, entities);
}
