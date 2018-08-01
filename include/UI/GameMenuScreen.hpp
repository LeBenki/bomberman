/*
** EPITECH PROJECT, 2018
** GameMenuScreen
** File description:
** Declaration of GameMenuScreen
*/

#ifndef INDIE_STUDIO_GAMEMENUSCREEN_HPP
	#define INDIE_STUDIO_GAMEMENUSCREEN_HPP

#include "AMenuScreen.hpp"
#include "iostream"

class GameMenuScreen : public AMenuScreen
{
public:
	GameMenuScreen(irr::gui::IGUIEnvironment *env,
			const irr::core::rect<irr::s32> &rect);
private:
};


#endif //INDIE_STUDIO_GAMEMENUSCREEN_HPP
