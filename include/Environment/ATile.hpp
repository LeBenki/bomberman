/*
** EPITECH PROJECT, 2018
** ATile
** File description:
** Declaration of ATile
*/

#ifndef INDIE_STUDIO_ATILE_HPP
	#define INDIE_STUDIO_ATILE_HPP

#include <irrlicht/irrlicht.h>
#include <string>
#include "ITile.hpp"
#include "BiomeManager.hpp"

class ATile : public ITile
{
public:
	ATile(BiomeManager::Name biome, Type type, char luaCharacter);
	void draw(irr::s32 x, irr::s32 y, irr::s32 titleSize) override;
	char getLuaCharacter() const final;
	Type getType() const final;
	~ATile() override;
protected:
	Type type;
	std::string texture;
	char luaCharacter;
	irr::scene::ISceneNode* ground;
	BiomeManager::Name biome;
};

#endif //INDIE_STUDIO_ATILE_HPP
