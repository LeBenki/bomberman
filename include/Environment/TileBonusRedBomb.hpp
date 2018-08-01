/*
** EPITECH PROJECT, 2018
** ATileBonusRedBomb
** File description:
** Declaration of ATileBonusRedBomb
*/

#ifndef INDIE_STUDIO_ATILEBONUSREDBOMB_HPP
	#define INDIE_STUDIO_ATILEBONUSREDBOMB_HPP

#include <Bomberman.hpp>
#include "ABonusTile.hpp"

class TileBonusRedBomb : public ABonusTile
{
public:
	explicit TileBonusRedBomb(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusRedBomb() override;
};

#endif //INDIE_STUDIO_ATILEBONUSREDBOMB_HPP
