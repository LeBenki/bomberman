/*
** EPITECH PROJECT, 2018
** Menu
** File description:
** Implementation of Menu
*/

#include <SaveManager.hpp>
#include "JoystickManager.hpp"
#include "Window.hpp"
#include "Menu.hpp"

Menu::Menu(Settings &s, Scene &scene) : settings(&s), scene(&scene),
	currentScreenId(Event::MenuItem::TITLESCREEN), oldScreenId(0)
{
	initMenuScreens(currentScreenId);
}

void Menu::initMenuScreens(int screenId)
{
	irr::gui::IGUIEnvironment *env = Window::device->getGUIEnvironment();
	irr::core::dimension2d<irr::u32> res = settings->getResolution();
	irr::core::rect<irr::s32> rect = irr::core::rect<irr::s32>(
		static_cast<irr::s32>(res.Width * 0.25),
		static_cast<irr::s32>(res.Height * 0.1),
		static_cast<irr::s32>(res.Width * 0.75),
		static_cast<irr::s32>(res.Height * 0.9));

	for (AMenuScreen *screen : screens) {
		delete screen;
	}
	env->getSkin()->setFont(env->getFont(ResourceManager::getMenuPath(ResourceManager::MENU_FONT).c_str()));
	screens.clear();
	screens.push_back(new TitleScreen(env, rect));
	screens.push_back(new VersusConfigScreen(env, rect));
	screens.push_back(new GameMenuScreen(env, rect));
	screens.push_back(new SettingsScreen(env, rect, *settings));
	screens[screenId]->toggle();
	currentScreenId = screenId;
	loadingScreen = env->addImage(env->getVideoDriver()->getViewPort(), 0);
	loadingScreen->setImage(env->getVideoDriver()->getTexture(ResourceManager::getMenuPath(ResourceManager::MENU_LOADING).c_str()));
	loadingScreen->setVisible(true);
	loadingScreen->setScaleImage(true);
}

void Menu::refresh(Event &events)
{
	loadingScreen->setVisible(false);
	for (std::pair<EventManager::Action, EventManager::InputType> event
		: EventManager::getEvents()) {
		if (event.first == EventManager::MENU
			 && event.second == EventManager::RELEASED)
			toggleDisplay();
	}
	for (const std::pair<Event::MenuItem, irr::gui::EGUI_EVENT_TYPE> &event
		: events.getGuiEvents()) {
		processEvent(event.first, event.second);
	}
}

void Menu::processEvent(Event::MenuItem id, irr::gui::EGUI_EVENT_TYPE type)
{
	if (type != irr::gui::EGET_BUTTON_CLICKED
		&& type != irr::gui::EGET_CHECKBOX_CHANGED
		&& type != irr::gui::EGET_SCROLL_BAR_CHANGED
		&& type != irr::gui::EGET_COMBO_BOX_CHANGED)
		return;
	switch (id) {
		case Event::MenuItem::PLAY_CAMPAIGN:
			showLoadingScreen();
			scene->newCampaignGame();
			setCurrentScreenId(Event::GAME_MENU);
			screens[currentScreenId]->toggle();
			return;
		case Event::MenuItem::PLAY_VERSUS:
			setCurrentScreenId(Event::MenuItem::PLAY_VERSUS);
			return;
		case Event::MenuItem::SETTINGS:
			setCurrentScreenId(Event::MenuItem::SETTINGS);
			return;
		case Event::MenuItem::GAME_MENU:
			setCurrentScreenId(Event::MenuItem::GAME_MENU);
			return;
		case Event::MenuItem ::EXIT_GAME:
			backToTitleScreen();
			return;
		case Event::MenuItem ::EXIT_PROGRAM:
			Window::device->closeDevice();
			return;
		case Event::RESOLUTION:
			resizeWindow();
			break;
		case Event::FULLSCREEN:
			fullscreen();
			break;
		case Event::LANGUAGE:
			changeLanguage();
			break;
		case Event::SHADOWS:
			toggleShadows();
			break;
		case Event::GRAPHICS:
			changeGraphics();
			break;
		case Event::PARTICLES:
			changeParticles();
			break;
		case Event::SPLITSCREEN:
			settings->setSplitScreen(!settings->isSplitScreen());
			break;
		case Event::MUSIC_VOLUME:
			changeMusicVolume();
			break;
		case Event::FX_VOLUME:
			changeFXVolume();
			break;
		case Event::MAP_WIDTH:
			break;
		case Event::MAP_HEIGHT:
			break;
		case Event::START_VERSUS:
			if (checkVersus())
			{
				showLoadingScreen();
				startVersusGame();
				setCurrentScreenId(Event::GAME_MENU);
				screens[currentScreenId]->toggle();
			}
			return;
		case Event::SAVE:
			saveGame();
			return;
		case Event::LOAD:
			loadGame();
			return;
		default:
			if (id == Event::PLAYER1 || id == Event::PLAYER1
				|| id == Event::PLAYER1 || id == Event::PLAYER1) {
				updatePlayers(id);
				return;
			}
			return;
	}
	if (!screens[Event::MenuItem::SETTINGS]->isVisible())
		setCurrentScreenId(Event::MenuItem::SETTINGS);
}

void Menu::toggleShadows()
{
	settings->setShadows(!settings->isShadows());
}

void Menu::fullscreen()
{
	settings->setFullscreen(!settings->isFullscreen());
	reloadWindow();
}

void Menu::changeLanguage()
{
	Window::settings.setLanguage((Settings::Language)(((irr::gui::IGUIComboBox *)Window::device
		->getGUIEnvironment()->getRootGUIElement()
		->getElementFromId(Event::LANGUAGE, true))->getSelected() + 1));
	initMenuScreens(currentScreenId);
	loadingScreen->setVisible(false);
}

void Menu::resizeWindow()
{
	auto *elem = (irr::gui::IGUIComboBox *)Window::device
		->getGUIEnvironment()->getRootGUIElement()
		->getElementFromId(Event::RESOLUTION, true);
	settings->setResolutionId(elem->getSelected());
	settings->setResolution(Settings::resolutions[elem->getSelected()]);
	reloadWindow();
}

void Menu::reloadWindow()
{
	for (auto screen : screens) {
		delete screen;
	}
	screens.clear();
	Window::device->getVideoDriver()->endScene();
	Window::device->closeDevice();
	Window::device->run();
	Window::device->drop();
	Window::device = irr::createDevice(irr::video::EDT_OPENGL,
		settings->getResolution(), 16, settings->isFullscreen(),
		true, true, &Window::event);
	JoystickManager::init();
	scene->setDevice(Window::device);
	scene->reload();
	initMenuScreens(currentScreenId);
	Window::device->getVideoDriver()->beginScene(true, true,
		irr::video::SColor(255, 255, 255, 255));
}

void Menu::toggleDisplay()
{
	switch (currentScreenId) {
		case Event::MenuItem::TITLESCREEN:
			return;
		case Event::MenuItem::PLAY_VERSUS:
			setCurrentScreenId(oldScreenId);
			oldScreenId = currentScreenId;
			break;
		case Event::MenuItem::GAME_MENU:
			screens[currentScreenId]->toggle();
			break;
		case Event::MenuItem::SETTINGS:
			setCurrentScreenId(oldScreenId);
			oldScreenId = currentScreenId;
			break;
	}
}

void Menu::updatePlayers(Event::MenuItem id)
{
	auto box = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(id, true);

	(void)box;
	return;
}

void Menu::startVersusGame()
{
	auto widthBox = (irr::gui::IGUISpinBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::MAP_WIDTH, true);
	auto heightBox = (irr::gui::IGUISpinBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::MAP_HEIGHT, true);
	auto biomeBox = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::BIOME, true);
	auto player1 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER1, true);
	auto player2 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER2, true);
	auto player3 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER3, true);
	auto player4 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER4, true);
	std::vector<Event::InputType> players;
	int controllers = 0;
	BiomeManager::Name biome =
		(BiomeManager::Name)biomeBox->getSelected() == BiomeManager::RANDOM
		? BiomeManager::getRandomBiome(1, 8) : (BiomeManager::Name)biomeBox->getSelected();

	for (irr::gui::IGUIComboBox *box : {player1, player2, player3, player4}) {
		if (box->getSelected() == Event::CONTROLLER1) {
			players.push_back((Event::InputType)(Event::CONTROLLER1 + controllers));
			controllers++;
		}
		else
			players.push_back((Event::InputType)box->getSelected());
	}
	scene->newBattleGame(static_cast<int>(widthBox->getValue()),
			     static_cast<int>(heightBox->getValue()), biome, players);
}

void Menu::setCurrentScreenId(int newId)
{
	oldScreenId = currentScreenId;
	screens[currentScreenId]->toggle();
	currentScreenId = newId;
	screens[currentScreenId]->toggle();
}
bool Menu::isOpen()
{
	for (AMenuScreen *screen : screens)
		if (screen->isVisible())
			return true;
	return false;
}

void Menu::showLoadingScreen()
{
	loadingScreen->setVisible(true);
	loadingScreen->draw();
}

void Menu::changeGraphics()
{
	auto box = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::GRAPHICS, true);

	settings->setQuality((Settings::Graphics)box->getSelected());
	scene->reload();
	scene->setReloaded(false);
}

void Menu::changeParticles()
{
	auto box = (irr::gui::IGUICheckBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PARTICLES, true);

	Window::settings.setParticles(box->isChecked());
	scene->reload();
	scene->setReloaded(false);
}

void Menu::changeMusicVolume()
{
	auto box = (irr::gui::IGUIScrollBar *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::MUSIC_VOLUME, true);

	Window::settings.setMusicVolume(box->getPos());
	SoundEngine::setMusicVolume((float)Window::settings.getMusicVolume() / 100);
}

void Menu::changeFXVolume()
{
	auto box = (irr::gui::IGUIScrollBar *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::FX_VOLUME, true);

	Window::settings.setFxVolume(box->getPos());
	SoundEngine::setEffectVolume((float)Window::settings.getFxVolume() / 100);
}

void Menu::backToTitleScreen()
{
	SoundEngine::playMusic("Title");
	showLoadingScreen();
	scene->clear();
	scene->initTitleScene();
	setCurrentScreenId(Event::TITLESCREEN);
	scene->setInGame(false);
	SoundEngine::playMusic("Title");
}

void Menu::saveGame()
{
	showLoadingScreen();
	SaveManager::saveScene(*scene);
	setCurrentScreenId(Event::GAME_MENU);
	screens[currentScreenId]->toggle();
}

void Menu::loadGame()
{
	std::ifstream file(ResourceManager::getSavePath());

	if (!file.is_open())
		return;
	showLoadingScreen();
	scene->clear();
	SaveManager::loadScene(ResourceManager::getSavePath(), *scene);
	scene->initSceneManager(Window::settings.isShadows());
	scene->initCamera();
	scene->setReloaded(true);
	scene->setInGame(true);
	setCurrentScreenId(Event::GAME_MENU);
	screens[currentScreenId]->toggle();
}

bool Menu::checkVersus()
{
	std::vector<Event::InputType> players;
	int controllers = 0;
	int keyboard = 0;
	int disabled = 0;

	auto player1 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER1, true);
	auto player2 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER2, true);
	auto player3 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER3, true);
	auto player4 = (irr::gui::IGUIComboBox *)Window::device->getGUIEnvironment()
		->getRootGUIElement()->getElementFromId(Event::PLAYER4, true);
	for (irr::gui::IGUIComboBox *box : {player1, player2, player3, player4}) {
		if (box->getSelected() == Event::KEYBOARD)
			++keyboard;
		if (box->getSelected() == Event::NONE)
			++disabled;
		if (box->getSelected() == Event::CONTROLLER1)
			++controllers;
	}
	return (!(controllers > JoystickManager::goodJoystickNum || keyboard > 1 || disabled > 2));
}
