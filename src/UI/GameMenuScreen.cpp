/*
** EPITECH PROJECT, 2018
** GameMenuScreen
** File description:
** Implementation of GameMenuScreen
*/

#include <Event.hpp>
#include <Window.hpp>
#include "GameMenuScreen.hpp"

GameMenuScreen::GameMenuScreen(irr::gui::IGUIEnvironment *env,
			       const irr::core::rect<irr::s32> &rect)
	: AMenuScreen(env, rect)
{
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("settings"), "", Event::SETTINGS, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("save"), "", Event::SAVE, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("menu"), "", Event::EXIT_GAME, parent));
	drawElements(env);
}