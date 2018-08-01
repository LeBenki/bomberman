/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Declaration of EventManager
*/

#ifndef CPP_INDIE_STUDIO_EVENTMANAGER_HPP
	#define CPP_INDIE_STUDIO_EVENTMANAGER_HPP

#include <utility>
#include <vector>
#include <map>
#include <irrlicht/irrlicht.h>
#include "Event.hpp"

class EventManager
{
public:
	enum Action {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_RIGHT,
		MOVE_LEFT,
		CAMERA_XUP,
		CAMERA_XDOWN,
		CAMERA_YUP,
		CAMERA_YDOWN,
		CAMERA_ZUP,
		CAMERA_ZDOWN,
		ATTACK,
		INVENTORY,
		EXIT,
		MENU,
		DAB,
		ACCEPT,
		SAVE,
		LOAD
	};
	enum InputType {
		PRESSED,
		RELEASED
	};
	static void refresh(Event &event);
	static std::vector<std::pair<Action, InputType>> getEvents();
private:
	static std::vector<std::pair<Action, InputType>> events;
};

#endif //CPP_INDIE_STUDIO_EVENTMANAGER_HPP
