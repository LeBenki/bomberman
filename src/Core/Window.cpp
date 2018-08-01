/*
** EPITECH PROJECT, 2018
** Window
** File description:
** Implementation of Window
*/

#include "JoystickManager.hpp"
#include "Window.hpp"

Event Window::event;

Settings Window::settings;

irr::IrrlichtDevice *Window::device = irr::createDevice(irr::video::EDT_OPENGL,
							settings.getResolution(), 16,
							settings.isFullscreen(), true, true, &event);

Window::Window() : scene(), menu(settings, scene), hud()
{
	JoystickManager::init();
}

void Window::open()
{
	int lastFPS = -1;
	scene.resetTimer();
	while (device->run()) {
		device->getVideoDriver()->beginScene(true, true,
			irr::video::SColor(255, 0, 0, 0));
		scene.refresh(event, menu.isOpen(), settings.isShadows(), settings.isSplitScreen());
		hud.refresh(scene);
		menu.refresh(event);
		int fps = device->getVideoDriver()->getFPS();
		if (lastFPS != fps) {
			irr::core::stringw str(L"Ecole pour casu FPS: ");
			str += fps;
			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
		device->getVideoDriver()->endScene();
	}
	device->drop();
}

void Window::close()
{

}

Window::~Window()
{

}
