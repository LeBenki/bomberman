/*
** EPITECH PROJECT, 2018
** MobBomberman
** File description:
** Declaration of MobBomberman
*/

#ifndef INDIE_STUDIO_MOBBOMBERMAN_HPP
	#define INDIE_STUDIO_MOBBOMBERMAN_HPP

#include "BombermanAIManager.hpp"
#include "Bomberman.hpp"
#include "AIManager.hpp"

class MobBomberman : public Bomberman
{
public:
	MobBomberman(irr::core::vector3df &pos, int teamId);
	~MobBomberman() override;
	void handleEvent(Map &map, std::vector<AEntity *> &entities) override;

private:
	BombermanAIManager _aiManager;
};


#endif /* INDIE_STUDIO_MOBBOMBERMAN_HPP */
