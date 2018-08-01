/*
** EPITECH PROJECT, 2018
** TileGate
** File description:
** Declaration of TileGate
*/

#ifndef INDIE_STUDIO_TILEGATE_HPP
	#define INDIE_STUDIO_TILEGATE_HPP

#include "ITile.hpp"
#include "BiomeManager.hpp"

class TileGate : public ITile
{
public:
	TileGate();
	void draw(irr::s32 x, irr::s32 y, irr::s32 tileSize) override;
	char getLuaCharacter() const override;
	Type getType() const override;
	void open();
	bool isIsOpen() const;
	~TileGate() override;
private:
	Type type;
	char luaCharacter;
	irr::scene::ISceneNode* ground;
	BiomeManager::Name biome;
	bool isOpen;
	irr::s32 x;
	irr::s32 y;
	irr::s32 tileSize;
};

#endif //INDIE_STUDIO_TILEGATE_HPP
