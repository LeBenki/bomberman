/*
** EPITECH PROJECT, 2018
** BombermanAIManager
** File description:
** Declaration of BombermanAIManager
*/

#ifndef INDIE_STUDIO_BOMBERMANAIMANAGER_HPP
	#define INDIE_STUDIO_BOMBERMANAIMANAGER_HPP

#include "Bomberman.hpp"
#include "AIManager.hpp"

class BombermanAIManager : public AIManager
{
public:
	BombermanAIManager(const std::string &scriptPath);
	void refresh(const Map &map, const Bomberman &bomberman, const std::vector<AEntity *> &entities);
	void sendBombNbr(int nbr);
	void sendPassWall(bool canPass);
	void sendMaxBomb(int max);
	void sendRange(int range);
};

#endif /* INDIE_STUDIO_BOMBERMANAIMANAGER_HPP */
