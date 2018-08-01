/*
** EPITECH PROJECT, 2018
** HUD
** File description:
** Declaration of HUD
*/

#ifndef INDIE_STUDIO_HUD_HPP
	#define INDIE_STUDIO_HUD_HPP

#include <irrlicht/irrlicht.h>
#include <iostream>
#include <iomanip>
#include "Scene.hpp"

class HUD
{
public:
	HUD();
	~HUD();
	void init(const Scene &scene);
	void createPlayerPanels(const Scene &scene);
	void drawPlayerPanel(const AEntity &entity, irr::s32 id);
	void drawPlayerBuffs(const Bomberman &entity,
			const irr::core::rect<irr::s32> &rect,
			irr::gui::IGUIWindow *parent);
	void refresh(Scene &scene);
	void replaceIcons(irr::s32 id);
	void reload(Scene &scene);
	const irr::core::stringw timerFormat(irr::s32 time);
	void gameOverCheck(const Scene &scene);
private:
	std::vector<irr::gui::IGUIWindow *> characterSheets;
	std::vector<std::vector<irr::gui::IGUIImage *>> icons;
	std::map<irr::s32, std::vector<irr::gui::IGUIStaticText *>> values;
	irr::core::dimension2du iconSize;
	irr::gui::IGUIStaticText *timer;
	irr::gui::IGUIStaticText *score;
	irr::gui::IGUIImage *gameOverImage;
};

#endif //INDIE_STUDIO_HUD_HPP
