/*
** EPITECH PROJECT, 2018
** TitleScreen
** File description:
** Declaration of TitleScreen
*/

#ifndef INDIE_STUDIO_TITLESCREEN_HPP
	#define INDIE_STUDIO_TITLESCREEN_HPP

#include "AMenuScreen.hpp"

class TitleScreen : public AMenuScreen
{
public:
	TitleScreen(irr::gui::IGUIEnvironment *env,
		const irr::core::rect<irr::s32> &rect);
	void toggle() override;
	bool isVisible() override;
private:
	irr::gui::IGUIImage *background;
};


#endif //INDIE_STUDIO_TITLESCREEN_HPP
