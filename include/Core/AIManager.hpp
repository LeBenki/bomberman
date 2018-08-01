/*
** EPITECH PROJECT, 2018
** AIManager
** File description:
** Declaration of AIManager
*/

#ifndef INDIE_STUDIO_AIMANAGER_HPP
	#define INDIE_STUDIO_AIMANAGER_HPP

#include <lua5.3/lua.hpp>
#include "EventManager.hpp"
#include "Map.hpp"
#include "AEntity.hpp"

class AIManager
{
public:
	AIManager(const std::string &scriptPath);
	~AIManager();
	void refresh(const Map &map, const AEntity &entity, const std::vector<AEntity *> &entities);
	void fillEventVector(int movement);
	const std::vector<std::pair<EventManager::Action, EventManager::InputType>> &getEvents();

protected:
	void sendMap(const Map &map);
	void sendPositions(const irr::core::vector3df &position, const std::vector<AEntity *> &entities);
	void getMovement();

protected:
	lua_State *_state;
	int _move;
	std::vector<std::pair<EventManager::Action, EventManager::InputType>>
		_events;
};


#endif /* INDIE_STUDIO_AIMANAGER_HPP */
