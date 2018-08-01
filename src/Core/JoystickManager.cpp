/*
** EPITECH PROJECT, 2018
** JoystickManager
** File description:
** Implementation of JoystickManager
*/

#include <iostream>
#include "Window.hpp"
#include "JoystickManager.hpp"

std::vector<std::vector<std::pair<EventManager::Action, EventManager::InputType>>> JoystickManager::events(4);
irr::core::array<irr::SJoystickInfo> JoystickManager::joystickInfo;
const irr::f32 JoystickManager::deadZone = 0.5;
const int JoystickManager::keyMaxNumber = 10;
int JoystickManager::goodJoystickNum = 0;

const std::map<int, EventManager::Action> JoystickManager::actions = {
	{ 0, EventManager::ATTACK},
};

void JoystickManager::init()
{
	goodJoystickNum = 0;
	joystickInfo.clear();
	if(Window::device->activateJoysticks(joystickInfo))
	{
		for(irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
		{
			if (joystickInfo[joystick].Buttons)
				++goodJoystickNum;
		}
	}
}

void JoystickManager::refresh(Event &event)
{
	for (int num = 0; num < goodJoystickNum; ++num)
	{
		const irr::SEvent::SJoystickEvent & joystickData = event.getJoystickState(num);

		irr::f32 moveHorizontal = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
		irr::f32 moveVertical = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;

		//KEEP for keys arrow
		auto povDegrees = static_cast<irr::u16>(joystickData.POV / 100);
		if(povDegrees < 360)
		{
			if(povDegrees > 0 && povDegrees < 180)
				moveHorizontal = 1.f;
			else if(povDegrees > 180)
				moveHorizontal = -1.f;

			if(povDegrees > 90 && povDegrees < 270)
				moveVertical = -1.f;
			else if(povDegrees > 270 || povDegrees < 90)
				moveVertical = +1.f;
		}
		events[num].clear();
		for (int i = 0 ; i < keyMaxNumber; ++i) {
			if (event.isJoystickKeyReleased(num, i) && actions.count(i))
				events[num].emplace_back(actions.at(i), EventManager::RELEASED);
		}
		if (moveHorizontal > deadZone)
			events[num].emplace_back(EventManager::MOVE_RIGHT, EventManager::PRESSED);
		if (moveHorizontal < -deadZone)
			events[num].emplace_back(EventManager::MOVE_LEFT, EventManager::PRESSED);
		if (moveVertical > deadZone)
			events[num].emplace_back(EventManager::MOVE_UP, EventManager::PRESSED);
		if (moveVertical < -deadZone)
			events[num].emplace_back(EventManager::MOVE_DOWN, EventManager::PRESSED);
	}
}

std::vector<std::pair<EventManager::Action, EventManager::InputType>> JoystickManager::getEvents(int i)
{
	return events[i];
}