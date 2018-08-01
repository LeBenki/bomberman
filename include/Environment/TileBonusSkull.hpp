/*
** EPITECH PROJECT, 2018
** ABonusSkull
** File description:
** Declaration of ABonusSkull
*/

#ifndef INDIE_STUDIO_ABONUSSKULL_HPP
	#define INDIE_STUDIO_ABONUSSKULL_HPP

#include "ABonusTile.hpp"

class TileBonusSkull : public ABonusTile
{
public:
	explicit TileBonusSkull(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusSkull() override;
};

#endif //INDIE_STUDIO_ABONUSSKULL_HPP
