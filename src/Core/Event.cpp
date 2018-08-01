/*
** EPITECH PROJECT, 2018
** Event.cpp
** File description:
** Event class
*/

#include <iostream>
#include "JoystickManager.hpp"
#include "Event.hpp"

Event::Event()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		keyIsDown[i] = false;
		keyIsReleased[i] = false;
	}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 10; ++j)
		{
			joyStickKeyIsDown[i][j] = false;
			joyStickKeyIsReleased[i][j] = false;
		}
}

bool Event::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		keyIsReleased[event.KeyInput.Key] = !event.KeyInput.PressedDown;
		return true;
	}
	else if (event.EventType == irr::EET_GUI_EVENT) {
		guiEvents[(Event::MenuItem)event.GUIEvent.Caller->getID()]
			= event.GUIEvent.EventType;
	}
	for (irr::u32 num = 0; num < JoystickManager::joystickInfo.size(); ++num)
	{
		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
		    && event.JoystickEvent.Joystick == num && JoystickManager::joystickInfo[num].Buttons)
		{
			joystickNum = (num - (JoystickManager::joystickInfo.size() - JoystickManager::goodJoystickNum)) % 4;
			joystickState[joystickNum] = event.JoystickEvent;
			for (int i = 0; i < JoystickManager::keyMaxNumber; ++i)
			{
				if (joystickState[joystickNum].IsButtonPressed(i))
				{
					joyStickKeyIsDown[joystickNum][i] = joystickState[joystickNum].IsButtonPressed(i);
				}
				else
				{
					if (joyStickKeyIsDown[joystickNum][i])
						joyStickKeyIsReleased[joystickNum][i] = true;
					joyStickKeyIsDown[joystickNum][i] = false;
				}
			}
		}
	}
	return false;
}


bool Event::isJoystickKeyReleased(int joy, int i)
{
	if (joyStickKeyIsReleased[joy][i]) {
		joyStickKeyIsReleased[joy][i] = false;
		return true;
	}
	return false;
}

bool Event::isJoystickKeyisDown(int joy, int i) const
{
	return joyStickKeyIsDown[joy][i];
}

bool Event::isKeyReleased(irr::EKEY_CODE keyCode)
{
	if (keyIsReleased[keyCode]) {
		keyIsReleased[keyCode] = false;
		return true;
	}
	return false;
}

bool Event::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return keyIsDown[keyCode];
}


std::map<Event::MenuItem , irr::gui::EGUI_EVENT_TYPE> Event::getGuiEvents()
{
	std::map<Event::MenuItem , irr::gui::EGUI_EVENT_TYPE> ret = guiEvents;

	guiEvents.clear();
	return ret;
}

const irr::SEvent::SJoystickEvent &Event::getJoystickState(int i) const
{
	return joystickState[i];
}
