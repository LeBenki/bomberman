/*
** EPITECH PROJECT, 2018
** JoystickManager
** File description:
** Declaration of JoystickManager
*/

#ifndef INDIE_STUDIO_JOYSTICKHANDLER_HPP
	#define INDIE_STUDIO_JOYSTICKHANDLER_HPP

#include <irrlicht/IEventReceiver.h>
#include <irrlicht/irrArray.h>
#include <map>
#include <vector>
#include "Event.hpp"
#include "EventManager.hpp"

class JoystickManager
{
public:
	static void init();
	static void refresh(Event &event);
	static std::vector<std::pair<EventManager::Action, EventManager::InputType>> getEvents(int);
	static const int keyMaxNumber;
	static irr::core::array<irr::SJoystickInfo> joystickInfo;
	static int goodJoystickNum;
private:
	static std::vector<std::vector<std::pair<EventManager::Action, EventManager::InputType>>> events;
	static const std::map<int, EventManager::Action> actions;
	static const irr::f32 deadZone;
};

#endif //INDIE_STUDIO_JOYSTICKHANDLER_HPP
