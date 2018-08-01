/*
** EPITECH PROJECT, 2018
** VersusConfigScreen
** File description:
** Declaration of VersusConfigScreen
*/

#ifndef INDIE_STUDIO_VERSUSCONFIGSCREEN_HPP
	#define INDIE_STUDIO_VERSUSCONFIGSCREEN_HPP

#include "irrlicht/irrlicht.h"
#include "AMenuScreen.hpp"

class VersusConfigScreen : public AMenuScreen
{
public:
	VersusConfigScreen(irr::gui::IGUIEnvironment *env,
		const irr::core::rect<irr::s32> &rect);
};


#endif //INDIE_STUDIO_VERSUSCONFIGSCREEN_HPP
