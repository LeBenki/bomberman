/*
** EPITECH PROJECT, 2018
** Menu
** File description:
** Declaration of Menu
*/

#ifndef INDIE_STUDIO_MENU_HPP
	#define INDIE_STUDIO_MENU_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include "AMenuScreen.hpp"
#include "Event.hpp"
#include "Scene.hpp"
#include "Settings.hpp"
#include "GameMenuScreen.hpp"
#include "SettingsScreen.hpp"
#include "TitleScreen.hpp"
#include "VersusConfigScreen.hpp"

class Menu
{
public:
	Menu(Settings &settings, Scene &scene);
	void initMenuScreens(int screenId);
	void toggleDisplay();
	void refresh(Event &events);
	void processEvent(Event::MenuItem id, irr::gui::EGUI_EVENT_TYPE type);
	void setCurrentScreenId(int currentScreenId);
	void toggleShadows();
	void fullscreen();
	void resizeWindow();
	bool isOpen();
	void changeLanguage();
	void reloadWindow();
	void updatePlayers(Event::MenuItem id);
	void startVersusGame();
	void showLoadingScreen();
	void changeGraphics();
	void changeParticles();
	void changeMusicVolume();
	void changeFXVolume();
	void backToTitleScreen();
	void saveGame();
	void loadGame();
	bool checkVersus();
private:
	Settings *settings;
	Scene *scene;
	std::vector<AMenuScreen *> screens;
	irr::gui::IGUIImage *loadingScreen;
	int currentScreenId;
	int oldScreenId;
};


#endif //INDIE_STUDIO_MENU_HPP
