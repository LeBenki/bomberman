/*
** EPITECH PROJECT, 2018
** Mob
** File description:
** Declaration of Mob
*/

#ifndef INDIE_STUDIO_MOB_HPP
	#define INDIE_STUDIO_MOB_HPP

#include <lua5.3/lua.hpp>
#include "EventManager.hpp"
#include "AEntity.hpp"
#include "AIManager.hpp"

class Mob : public AEntity
{
public:
	Mob(irr::core::vector3df &pos, int, BiomeManager::Name biome);
	~Mob() override;
	void handleEvent(Map &map, std::vector<AEntity *> &entities) override;

private:
	AIManager _manager;
};

#endif //INDIE_STUDIO_MOB_HPP
