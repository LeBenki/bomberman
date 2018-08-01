/*
** EPITECH PROJECT, 2018
** SettingsScreen
** File description:
** Implementation of SettingsScreen
*/

#include <Window.hpp>
#include "SettingsScreen.hpp"

SettingsScreen::SettingsScreen(irr::gui::IGUIEnvironment *env,
				const irr::core::rect<irr::s32> &rect,
				const Settings &settings)
	: AMenuScreen(env, rect)
{
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("resolution"), Event::RESOLUTION, parent));
	elements.push_back(MenuElement(MenuElement::CHECKBOX,
		"", Lang::getWText("fullScreen"), Event::FULLSCREEN, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("gameQuality"), Event::GRAPHICS, parent));
	elements.push_back(MenuElement(MenuElement::CHECKBOX,
		"", Lang::getWText("shadows"), Event::SHADOWS, parent));
	elements.push_back(MenuElement(MenuElement::SCROLLBAR,
		"", Lang::getWText("musicVolume"), Event::MUSIC_VOLUME, parent));
	elements.push_back(MenuElement(MenuElement::SCROLLBAR,
		"", Lang::getWText("fxVolume"), Event::FX_VOLUME, parent));
	elements.push_back(MenuElement(MenuElement::COMBOBOX,
		"", Lang::getWText("language"), Event::LANGUAGE, parent));
	elements.push_back(MenuElement(MenuElement::CHECKBOX,
		"", Lang::getWText("particles"), Event::PARTICLES, parent));
	elements.push_back(MenuElement(MenuElement::CHECKBOX,
		"", Lang::getWText("splitScreen"), Event::SPLITSCREEN, parent));
	drawElements(env);
	initBoxesStatus(env, settings);
}

void SettingsScreen::initBoxesStatus(irr::gui::IGUIEnvironment *env, const Settings &settings)
{
	((irr::gui::IGUIComboBox *)env->getRootGUIElement()->getElementFromId(Event::RESOLUTION, true))->setSelected(settings.getResolutionId());
	((irr::gui::IGUICheckBox *)env->getRootGUIElement()->getElementFromId(Event::FULLSCREEN, true))->setChecked(settings.isFullscreen());
	((irr::gui::IGUIComboBox *)env->getRootGUIElement()->getElementFromId(Event::GRAPHICS, true))->setSelected(settings.getQuality());
	((irr::gui::IGUICheckBox *)env->getRootGUIElement()->getElementFromId(Event::SHADOWS, true))->setChecked(settings.isShadows());
	((irr::gui::IGUIScrollBar *)env->getRootGUIElement()->getElementFromId(Event::MUSIC_VOLUME, true))->setPos(Window::settings.getMusicVolume());
	((irr::gui::IGUIScrollBar *)env->getRootGUIElement()->getElementFromId(Event::FX_VOLUME, true))->setPos(Window::settings.getFxVolume());
	((irr::gui::IGUIComboBox *)env->getRootGUIElement()->getElementFromId(Event::LANGUAGE, true))->setSelected(Window::settings.getLanguage() - 1);
	((irr::gui::IGUICheckBox *)env->getRootGUIElement()->getElementFromId(Event::PARTICLES, true))->setChecked(Window::settings.isParticles());
	((irr::gui::IGUICheckBox *)env->getRootGUIElement()->getElementFromId(Event::SPLITSCREEN, true))->setChecked(settings.isSplitScreen());
}