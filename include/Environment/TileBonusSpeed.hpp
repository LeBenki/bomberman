/*
** EPITECH PROJECT, 2018
** TileBonusSpeed
** File description:
** Declaration of TileBonusSpeed
*/

#ifndef INDIE_STUDIO_TILEBONUSSPEED_HPP
	#define INDIE_STUDIO_TILEBONUSSPEED_HPP

#include <Bomberman.hpp>
#include "ABonusTile.hpp"

class TileBonusSpeed : public ABonusTile
{
public:
	explicit TileBonusSpeed(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusSpeed() override;

};

#endif //INDIE_STUDIO_TILEBONUSSPEED_HPP
