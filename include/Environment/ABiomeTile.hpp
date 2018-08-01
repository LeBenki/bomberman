/*
** EPITECH PROJECT, 2018
** AnimatedTile
** File description:
** Declaration of AnimatedTile
*/

#ifndef INDIE_STUDIO_ANIMATEDTILE_HPP
	#define INDIE_STUDIO_ANIMATEDTILE_HPP

#include <irrlicht/irrTypes.h>
#include <irrlicht/IrrlichtDevice.h>
#include <string>
#include "ATile.hpp"
#include "BiomeManager.hpp"

class ABiomeTile : public ATile
{
public:
	ABiomeTile(BiomeManager::Name biome, Type type, char luaCharacter);
	void draw(irr::s32 x, irr::s32 y, irr::s32 titleSize) override;
	~ABiomeTile() override;
protected:
	std::string modelTexture;
	std::string model;
	irr::scene::IAnimatedMeshSceneNode *wall;
};

#endif //INDIE_STUDIO_ANIMATEDTILE_HPP
