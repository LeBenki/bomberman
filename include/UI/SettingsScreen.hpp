/*
** EPITECH PROJECT, 2018
** SettingsScreen
** File description:
** Declaration of SettingsScreen
*/

#ifndef INDIE_STUDIO_SETTINGSSCREEN_HPP
	#define INDIE_STUDIO_SETTINGSSCREEN_HPP

#include "AMenuScreen.hpp"
#include "Settings.hpp"

class SettingsScreen : public AMenuScreen
{
public:
	SettingsScreen(irr::gui::IGUIEnvironment *env,
			const irr::core::rect<irr::s32> &rect,
			const Settings &settings);
	void initBoxesStatus(irr::gui::IGUIEnvironment *env, const Settings &settings);
};


#endif //INDIE_STUDIO_SETTINGSSCREEN_HPP
