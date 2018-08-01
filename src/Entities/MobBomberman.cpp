/*
** EPITECH PROJECT, 2018
** MobBomberman
** File description:
** Implementation of MobBomberman
*/

#include "MobBomberman.hpp"

MobBomberman::MobBomberman(irr::core::vector3df &pos, int teamId)
	: Bomberman(pos, teamId, Event::InputType::AI), _aiManager(ResourceManager::getAiPath(ResourceManager::AI_BOMBERMAN))
{
}

MobBomberman::~MobBomberman() = default;

void MobBomberman::handleEvent(Map &map, std::vector<AEntity *> &entities)
{
	_aiManager.refresh(map, *this, entities);
	doBombermanThings(_aiManager.getEvents(), map, entities);
}
