/*
** EPITECH PROJECT, 2018
** TileBonusShield
** File description:
** Declaration of TileBonusShield
*/

#ifndef INDIE_STUDIO_TILEBONUSSHIELD_HPP
	#define INDIE_STUDIO_TILEBONUSSHIELD_HPP

#include <irrlicht/irrTypes.h>
#include <string>
#include <Bomberman.hpp>
#include "ABonusTile.hpp"

class TileBonusShield  : public ABonusTile
{
public:
	explicit TileBonusShield(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusShield() override;
};

#endif //INDIE_STUDIO_TILEBONUSSHIELD_HPP
