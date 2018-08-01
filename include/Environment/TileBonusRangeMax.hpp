/*
** EPITECH PROJECT, 2018
** ABonusRangeMax
** File description:
** Declaration of ABonusRangeMax
*/

#ifndef INDIE_STUDIO_ABONUSRANGEMAX_HPP
	#define INDIE_STUDIO_ABONUSRANGEMAX_HPP

#include "ABonusTile.hpp"
#include "BiomeManager.hpp"

class TileBonusRangeMax  : public ABonusTile
{
public:
	explicit TileBonusRangeMax(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusRangeMax() override;
};

#endif //INDIE_STUDIO_ABONUSRANGEMAX_HPP
