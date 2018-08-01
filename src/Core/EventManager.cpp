/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Implementation of EventManager
*/

#include <iostream>
#include "EventManager.hpp"

std::vector<std::pair<EventManager::Action, EventManager::InputType>> EventManager::events;

static std::map<irr::EKEY_CODE, EventManager::Action> actions = {
	{ irr::KEY_KEY_Z, EventManager::Action::MOVE_UP },
	{ irr::KEY_KEY_Q, EventManager::Action::MOVE_LEFT },
	{ irr::KEY_KEY_S, EventManager::Action::MOVE_DOWN },
	{ irr::KEY_KEY_D, EventManager::Action::MOVE_RIGHT },
	{ irr::KEY_UP, EventManager::Action::CAMERA_ZUP },
	{ irr::KEY_DOWN, EventManager::Action::CAMERA_ZDOWN },
	{ irr::KEY_LEFT, EventManager::Action::CAMERA_XDOWN },
	{ irr::KEY_RIGHT, EventManager::Action::CAMERA_XUP },
	{ irr::KEY_PRIOR, EventManager::Action::CAMERA_YDOWN },
	{ irr::KEY_NEXT, EventManager::Action::CAMERA_YUP },
	{ irr::KEY_SPACE, EventManager::Action::ATTACK },
	{ irr::KEY_F10, EventManager::Action::EXIT },
	{ irr::KEY_KEY_E, EventManager::Action::DAB },
	{ irr::KEY_ESCAPE, EventManager::Action::MENU },
	{ irr::KEY_KEY_K, EventManager::Action::SAVE },
	{ irr::KEY_KEY_L, EventManager::Action::LOAD }
};

void EventManager::refresh(Event &event)
{
	events.clear();
	for (auto &line : actions) {
		if (event.isKeyDown(line.first))
			events.push_back({line.second, PRESSED});
		else if (event.isKeyReleased(line.first))
			events.push_back({line.second, RELEASED});
	}
}

std::vector<std::pair<EventManager::Action, EventManager::InputType>>
	EventManager::getEvents()
{
	return events;
}
