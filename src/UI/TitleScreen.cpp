/*
** EPITECH PROJECT, 2018
** TitleScreen
** File description:
** Implementation of TitleScreen
*/

#include <ResourceManager.hpp>
#include "TitleScreen.hpp"

TitleScreen::TitleScreen(irr::gui::IGUIEnvironment *env,
	const irr::core::rect<irr::s32> &rect) : AMenuScreen(env, rect)
{
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("campaign"), "", Event::PLAY_CAMPAIGN, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("versus"), "", Event::PLAY_VERSUS, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("load"), "", Event::LOAD, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("settings"), "", Event::SETTINGS, parent));
	elements.push_back(MenuElement(MenuElement::BUTTON,
		Lang::getWText("exit"), "", Event::EXIT_PROGRAM, parent));
	drawElements(env);
	parent->setVisible(true);
	background = env->addImage(env->getVideoDriver()->getViewPort());
	background->setImage(env->getVideoDriver()->getTexture(ResourceManager::getMenuPath(ResourceManager::MENU_MAIN_BACKGROUND).c_str()));
	background->setScaleImage(true);
	background->setVisible(false);
	background->setUseAlphaChannel(true);
	background->addChild(parent);
}

void TitleScreen::toggle()
{
	background->setVisible(!background->isVisible());
}

bool TitleScreen::isVisible()
{
	return background->isVisible();
}