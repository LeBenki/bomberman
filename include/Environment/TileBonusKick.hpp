/*
** EPITECH PROJECT, 2018
** TileBonusKick
** File description:
** Declaration of TileBonusKick
*/

#ifndef INDIE_STUDIO_TILEBONUSKICK_HPP
	#define INDIE_STUDIO_TILEBONUSKICK_HPP

#include "ABonusTile.hpp"

class TileBonusKick : public ABonusTile
{
public:
	explicit TileBonusKick(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusKick() override;
};

#endif //INDIE_STUDIO_TILEBONUSKICK_HPP
