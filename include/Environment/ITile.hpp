/*
** EPITECH PROJECT, 2018
** ITile
** File description:
** Declaration of ITile
*/

#ifndef INDIE_STUDIO_ITILE_HPP
	#define INDIE_STUDIO_ITILE_HPP

#include <irrlicht/irrlicht.h>

class ITile
{
public:
	enum Type {
		HARD_WALL,
		SOFT_WALL,
		FIRE,
		EMPTY,
		BONUS,
		GATE
	};
	virtual void draw(irr::s32 x, irr::s32 y, irr::s32 titleSize) = 0;
	virtual Type getType() const = 0;
	virtual char getLuaCharacter() const = 0;
	virtual ~ITile() = default;
};

#endif //INDIE_STUDIO_ITILE_HPP
