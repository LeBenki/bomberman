/*
** EPITECH PROJECT, 2018
** Event.hpp
** File description:
** event class header
*/

#ifndef EVENT_HPP_
	#define EVENT_HPP_

#include <vector>
#include <map>
#include <irrlicht/irrlicht.h>

class Event : public irr::IEventReceiver
{
public:
	enum MenuItem {
		TITLESCREEN = 0,
		PLAY_VERSUS,
		GAME_MENU,
		SETTINGS,
		PLAY_CAMPAIGN,
		EXIT_GAME,
		EXIT_PROGRAM,
		SAVE,
		LOAD,
		RESOLUTION,
		FULLSCREEN,
		GRAPHICS,
		SHADOWS,
		MUSIC_VOLUME,
		FX_VOLUME,
		LANGUAGE,
		SPLITSCREEN,
		PARTICLES,
		MAP_WIDTH,
		MAP_HEIGHT,
		BIOME,
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		START_VERSUS
	};
	enum InputType {
		NONE = 0,
		AI,
		KEYBOARD,
		CONTROLLER1,
		CONTROLLER2,
		CONTROLLER3,

	};
	Event();
	bool OnEvent(const irr::SEvent &event) override;
	bool isKeyDown(irr::EKEY_CODE keyCode) const;
	bool isKeyReleased(irr::EKEY_CODE keyCode);
	const irr::SEvent::SJoystickEvent &getJoystickState(int) const;
	std::map<Event::MenuItem, irr::gui::EGUI_EVENT_TYPE> getGuiEvents();
	bool isJoystickKeyisDown(int, int i) const;
	bool isJoystickKeyReleased(int, int i);
protected:
	bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
	bool keyIsReleased[irr::KEY_KEY_CODES_COUNT];
	bool joyStickKeyIsDown[4][10];
	bool joyStickKeyIsReleased[4][10];
	std::map<Event::MenuItem, irr::gui::EGUI_EVENT_TYPE> guiEvents;
	irr::SEvent::SJoystickEvent joystickState[4];
	int joystickNum;
};

#endif /* !EVENT_HPP_ */
