/*
** EPITECH PROJECT, 2018
** BombermanAIManager
** File description:
** Implementation of BombermanAIManager
*/

#include "BombermanAIManager.hpp"

BombermanAIManager::BombermanAIManager(const std::string &scriptPath)
	: AIManager(scriptPath)
{

}

void BombermanAIManager::sendBombNbr(int nbr)
{
	lua_pushnumber(_state, nbr);
	lua_setglobal(_state, "nbBomb");
}


void BombermanAIManager::sendPassWall(bool canPass)
{
	if (canPass)
		lua_pushnumber(_state, 1);
	else if (!canPass)
		lua_pushnumber(_state, 0);
	lua_setglobal(_state, "passWall");
}

void BombermanAIManager::refresh(const Map &map, const Bomberman &bomberman,
				 const std::vector<AEntity *> &entities)
{
	sendBombNbr(bomberman.getCurrentBombs());
	sendPassWall(bomberman.isCanPassSoft());
	sendMaxBomb(bomberman.getMaxBombs());
	sendRange(bomberman.getRange());
	AIManager::refresh(map, bomberman, entities);
}

void BombermanAIManager::sendMaxBomb(int max)
{
	lua_pushnumber(_state, max);
	lua_setglobal(_state, "maxBomb");
}

void BombermanAIManager::sendRange(int range)
{
	lua_pushnumber(_state, range);
	lua_setglobal(_state, "range");
}
