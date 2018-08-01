/*
** EPITECH PROJECT, 2018
** TileBonusBomb
** File description:
** Declaration of TileBonusBomb
*/

#ifndef INDIE_STUDIO_TILEBONUSBOMB_HPP
	#define INDIE_STUDIO_TILEBONUSBOMB_HPP

#include <Bomberman.hpp>
#include "ABonusTile.hpp"

class TileBonusBomb : public ABonusTile
{
public:
	explicit TileBonusBomb(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusBomb() override;
};

#endif //INDIE_STUDIO_TILEBONUSBOMB_HPP
