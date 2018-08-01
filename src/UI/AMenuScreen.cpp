/*
** EPITECH PROJECT, 2018
** AMenuScreen
** File description:
** Implementation of AMenuScreen
*/

#include <ResourceManager.hpp>
#include "AMenuScreen.hpp"

AMenuScreen::AMenuScreen(irr::gui::IGUIEnvironment *env,
			 const irr::core::rect<irr::s32> &rect) : size(rect)
{
	parent = env->addImage(rect);
	parent->setImage(env->getVideoDriver()->getTexture(ResourceManager::getMenuPath(ResourceManager::MENU_BACKGROUND).c_str()));
	parent->setScaleImage(true);
	parent->setVisible(false);
	parent->setUseAlphaChannel(true);
}

AMenuScreen::~AMenuScreen()
{
	parent->remove();
}

void AMenuScreen::toggle()
{
	parent->setVisible(!parent->isVisible());
}

void AMenuScreen::drawElements(irr::gui::IGUIEnvironment *env)
{
	for (unsigned int i = 0; i < elements.size(); i++) {
		elements[i].draw(*env, size, i, elements.size());
	}
}

bool AMenuScreen::isVisible()
{
	return parent->isVisible();
}