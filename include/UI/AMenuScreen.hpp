/*
** EPITECH PROJECT, 2018
** AMenuScreen
** File description:
** Declaration of AMenuScreen
*/

#ifndef INDIE_STUDIO_AMENUSCREEN_HPP
	#define INDIE_STUDIO_AMENUSCREEN_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include <utility>
#include "Lang.hpp"
#include "MenuElement.hpp"

class AMenuScreen
{
public:
	AMenuScreen(irr::gui::IGUIEnvironment *env,
			const irr::core::rect<irr::s32> &rect);
	virtual ~AMenuScreen();
	virtual void toggle();
	void drawElements(irr::gui::IGUIEnvironment *env);
	virtual bool isVisible();
protected:
	irr::core::rect<irr::s32> size;
	std::vector<MenuElement> elements;
	irr::gui::IGUIImage *parent;
};


#endif //INDIE_STUDIO_AMENUSCREEN_HPP
