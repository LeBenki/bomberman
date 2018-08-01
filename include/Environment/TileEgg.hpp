/*
** EPITECH PROJECT, 2018
** TileEgg
** File description:
** Declaration of TileEgg
*/

#ifndef INDIE_STUDIO_TILEEGG_HPP
	#define INDIE_STUDIO_TILEEGG_HPP

#include "ABonusTile.hpp"

class TileEgg : public ABonusTile
{
public:
	explicit TileEgg(BiomeManager::Name biome, Type type = BONUS, char luaCharacter = 'B');
	void buffBomberman(Bomberman &bomberman) override;
	~TileEgg() override;
private:
	std::string model;
	std::string texture;
	irr::scene::IAnimatedMeshSceneNode *wall;
};

#endif //INDIE_STUDIO_TILEEGG_HPP
