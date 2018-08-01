/*
** EPITECH PROJECT, 2018
** versusConfigScreen
** File description:
** Implementation of VersusConfigScreen
*/

#include "VersusConfigScreen.hpp"

VersusConfigScreen::VersusConfigScreen(irr::gui::IGUIEnvironment *env,
	const irr::core::rect<irr::s32> &rect)
	: AMenuScreen(env, rect)
{
	elements.push_back(MenuElement(MenuElement::SPINNERBOX,
		"", Lang::getWText("mapWidth"), Event::MAP_WIDTH, parent));
	elements.push_back(MenuElement(MenuElement::SPINNERBOX,
		"", Lang::getWText("mapHeight"), Event::MAP_HEIGHT, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("biome"), Event::BIOME, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("player") + " 1", Event::PLAYER1, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("player") + " 2", Event::PLAYER2, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("player") + " 3", Event::PLAYER3, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("player") + " 4", Event::PLAYER4, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("play"), "", Event::START_VERSUS, parent));
	drawElements(env);
}
