/*
** EPITECH PROJECT, 2018
** TileBonusRange
** File description:
** Declaration of TileBonusRange
*/

#ifndef INDIE_STUDIO_TILEBONUSRANGE_HPP
#define INDIE_STUDIO_TILEBONUSRANGE_HPP


#include "ABonusTile.hpp"
#include "TileBonusBomb.hpp"

class TileBonusRange : public ABonusTile
{
public:
	explicit TileBonusRange(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusRange() override;
};


#endif //INDIE_STUDIO_TILEBONUSRANGE_HPP
