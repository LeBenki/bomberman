/*
** EPITECH PROJECT, 2018
** Mount
** File description:
** Implementation of Mount
*/

#include "Mount.hpp"

Mount::Mount(irr::core::vector3df &pos, int teamId, AEntity::Type type, bool isMD2)
	: AEntity(ResourceManager::MOUNT, pos, teamId, type, isMD2)
{

}

Mount::~Mount()
{

}

void Mount::handleEvent(Map &map, std::vector<AEntity *> &entities)
{
	(void)map;
	(void)entities;
}

void Mount::move(const irr::core::vector3df &vec, Map &map,
		 std::vector<AEntity *> &entities,
		 irr::core::vector3df &oldPositions)
{
	(void)vec;
	(void)map;
	(void)entities;
	(void)oldPositions;
}
