/*
** EPITECH PROJECT, 2018
** TileBonusPassSoftWall
** File description:
** Declaration of TileBonusPassSoftWall
*/

#ifndef INDIE_STUDIO_TILEBONUSPASSSOFTWALL_HPP
	#define INDIE_STUDIO_TILEBONUSPASSSOFTWALL_HPP

#include "BiomeManager.hpp"
#include "ABonusTile.hpp"

class TileBonusPassSoftWall : public ABonusTile
{
public:
	explicit TileBonusPassSoftWall(BiomeManager::Name biome, Type type = BONUS);
	void buffBomberman(Bomberman &bomberman) override;
	~TileBonusPassSoftWall() override;
};

#endif //INDIE_STUDIO_TILEBONUSPASSSOFTWALL_HPP
