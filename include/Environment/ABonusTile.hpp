/*
** EPITECH PROJECT, 2018
** ABonusTile
** File description:
** Declaration of ABonusTile
*/

#ifndef INDIE_STUDIO_ABONUSTILE_HPP
	#define INDIE_STUDIO_ABONUSTILE_HPP

#include "ATile.hpp"
#include "Bomberman.hpp"
#include "ResourceManager.hpp"

class ABonusTile : public ATile
{
public:
	ABonusTile(ResourceManager::Name resName, BiomeManager::Name biome, Type type, char luaCharacter);
	void draw(irr::s32 x, irr::s32 y, irr::s32 titleSize) override;
	void refresh();
	virtual void buffBomberman(Bomberman &bomberman) = 0;
	~ABonusTile() override;
protected:
	irr::scene::IAnimatedMeshSceneNode *wall;
	irr::f32 rotY;
	ResourceManager::Name resName;
};

#endif //INDIE_STUDIO_ABONUSTILE_HPP
