/*
** EPITECH PROJECT, 2018
** AIManager
** File description:
** Implementation of AIManager
*/

#include "AIManager.hpp"

AIManager::AIManager(const std::string &scriptPath)
{
	_state = luaL_newstate();
	luaL_loadfile(_state, scriptPath.c_str());
	lua_setglobal(_state, "startScript");
	luaL_openlibs(_state);
	_move = 0;
}

AIManager::~AIManager()
{
	if (_state)
		lua_close(_state);
}

void AIManager::refresh(const Map &map, const AEntity &entity, const std::vector<AEntity *> &entities)
{
	sendMap(map);
	sendPositions(entity.getPosition(), entities);
	lua_getglobal(_state, "startScript");
	lua_pcall(_state, 0, LUA_MULTRET, 0);
	getMovement();
	fillEventVector(_move);
}

void AIManager::fillEventVector(int movement)
{
	EventManager::Action action{};

	_events.clear();
	switch (movement) {
		case 1:
			action = EventManager::MOVE_UP;
			break;
		case 2:
			action = EventManager::MOVE_RIGHT;
			break;
		case -1:
			action = EventManager::MOVE_DOWN;
			break;
		case -2:
			action = EventManager::MOVE_LEFT;
			break;
		case 26:
			action = EventManager::ATTACK;
			break;
		default:
			break;
	}
	if (movement != 0) {
		if (movement == 26)
			_events.emplace_back(action, EventManager::RELEASED);
		else
			_events.emplace_back(action, EventManager::PRESSED);
	}
}

const std::vector<std::pair<EventManager::Action, EventManager::InputType>> &
AIManager::getEvents()
{
	return _events;
}

void AIManager::sendMap(const Map &map)
{
	std::vector<std::string> luaMap = map.getMapInLuaFormat();
	int i = 1;

	lua_newtable(_state);
	for (auto &line : luaMap) {
		lua_pushstring(_state, line.c_str());
		lua_rawseti(_state, -2, i++);
	}
	lua_setglobal(_state, "map");
	lua_pushnumber(_state, map.getTileSize());
	lua_setglobal(_state, "tileSize");
}

void AIManager::sendPositions(const irr::core::vector3df &position,
			      const std::vector<AEntity *> &entities)
{
	irr::core::vector3df ePos;
	irr::core::vector3df bombPos;
	int i = 1;

	lua_newtable(_state);
	for (auto const &entity : entities) {
		if (entity->getType() == AEntity::Type::BombermanType) {
			ePos = entity->getPosition();
			if (ePos.Z != position.Z || ePos.X != position.X) {
				lua_pushnumber(_state, ePos.Z);
				lua_rawseti(_state, -2, i);
				lua_pushnumber(_state, ePos.X);
				lua_rawseti(_state, -2, i + 1);
				i += 2;
			}
		}
	}
	i = 1;
	lua_setglobal(_state, "posEn");
	lua_newtable(_state);
	for (auto const &entity : entities) {
		if (entity->getType() == AEntity::Type::BombType) {
			bombPos = entity->getPosition();
			lua_pushnumber(_state, bombPos.Z);
			lua_rawseti(_state, -2, i);
			lua_pushnumber(_state, bombPos.X);
			lua_rawseti(_state, -2, i + 1);
			i += 2;
		}
	}
	lua_setglobal(_state, "posBomb");
	lua_newtable(_state);
	lua_pushnumber(_state, position.Z);
	lua_rawseti(_state, -2, 1);
	lua_pushnumber(_state, position.X);
	lua_rawseti(_state, -2, 2);
	lua_setglobal(_state, "pos");
	lua_pushnumber(_state, _move);
	lua_setglobal(_state, "move");
}

void AIManager::getMovement()
{
	lua_getglobal(_state, "move");
	_move = (int)lua_tonumber(_state, -1);
	lua_pop(_state, 1);
}
