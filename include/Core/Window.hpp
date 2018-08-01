/*
** EPITECH PROJECT, 2018
** Window
** File description:
** Declaration of Window
*/

#ifndef CPP_INDIE_STUDIO_WINDOW_HPP
	#define CPP_INDIE_STUDIO_WINDOW_HPP

#include <irrlicht/irrlicht.h>
#include <irrlicht/IrrlichtDevice.h>
#include "Event.hpp"
#include "Scene.hpp"
#include "Menu.hpp"
#include "HUD.hpp"

class Window
{
public:
	Window();
	void open();
	void close();
	virtual ~Window();
	static irr::IrrlichtDevice *device;
	static Event event;
	static Settings settings;
private:
	Scene scene;
	Menu menu;
	HUD hud;
};

#endif //CPP_INDIE_STUDIO_WINDOW_HPP
