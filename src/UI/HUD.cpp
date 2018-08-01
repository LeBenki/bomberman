/*
** EPITECH PROJECT, 2018
** HUD
** File description:
** Implementation of HUD
*/

#include <Window.hpp>
#include "HUD.hpp"

std::vector<ResourceManager::Name> buffIcons = {
	ResourceManager::BONUSBOMB,
	ResourceManager::BONUSRANGE,
	ResourceManager::BONUSEGG,
	ResourceManager::BONUSPASSSOFT,
	ResourceManager::BONUSKICK,
	ResourceManager::BONUSREDBOMB,
	ResourceManager::BONUSSHIELD,
	ResourceManager::BONUSSKULL
};

HUD::HUD() : iconSize(10, 10), timer(nullptr), score(nullptr),
	gameOverImage(nullptr)
{
	for (int i = 0; i < 4; i++) {
		icons.push_back(std::vector<irr::gui::IGUIImage *>());
		characterSheets.push_back(nullptr);
	}
	timer = nullptr;
}

HUD::~HUD()
{
}

void HUD::init(const Scene &scene)
{
	irr::gui::IGUIEnvironment *env = Window::device->getGUIEnvironment();
	irr::core::dimension2du size = Window::settings.getResolution();
	irr::gui::IGUIImage *timerBg = env->addImage(irr::core::rect<irr::s32>(
		(irr::s32)(size.Width / 2 - size.Width * 0.1),
		(irr::s32)0,
		(irr::s32)(size.Width / 2 + size.Width * 0.1),
		(irr::s32)(size.Height * 0.075)));
	irr::core::rect<irr::s32> scorePos((irr::s32)(0),
		(irr::s32)(size.Height * 0.25),
		(irr::s32)(size.Width * 0.15),
		(irr::s32)(size.Height * 0.25 + 50));

	timerBg->setImage(env->getVideoDriver()->getTexture(ResourceManager::getResIcon(ResourceManager::TIMER_HUD).c_str()));
	timerBg->setScaleImage(true);
	timerBg->setUseAlphaChannel(true);
	timerBg->setVisible(false);
	timer = env->addStaticText(L"00:00", irr::core::rect<irr::s32>(0, 0,
		timerBg->getAbsolutePosition().getWidth(),
		timerBg->getAbsolutePosition().getHeight() - (irr::u32)(size.Height * 0.025)),
			false, true, timerBg);
	timer->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	timer->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	createPlayerPanels(scene);
	score = env->addStaticText(L"score: 0", scorePos, false, true);
	score->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	score->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

void HUD::createPlayerPanels(const Scene &scene)
{
	for (AEntity *entity : scene.getEntities()) {
		if (entity->getType() == AEntity::BombermanType) {
			drawPlayerPanel(*entity, entity->getTeamId());
		}
	}
}

void HUD::drawPlayerPanel(const AEntity &entity, irr::s32 id)
{
	irr::gui::IGUIEnvironment *env = Window::device->getGUIEnvironment();
	irr::core::dimension2du size = Window::settings.getResolution();
	irr::core::rect<irr::s32> rect((irr::s32)(id % 2 == 0 ? size.Width - size.Width * 0.15 : 0),
					(irr::s32)(id > 2 ? size.Height - size.Height * 0.25 : size.Height * 0.1),
					(irr::s32)(id % 2 == 0 ? size.Width: size.Width * 0.15),
					(irr::s32)(id > 2 ? size.Height - size.Height * 0.1 : size.Height * 0.25));

	iconSize = irr::core::dimension2du((irr::u32)rect.getWidth() / 10, (irr::u32)rect.getHeight() / 5);
	irr::gui::IGUIWindow *parent = env->addWindow(rect);
	characterSheets[entity.getTeamId() - 1] = parent;
	parent->setDrawTitlebar(false);
	parent->setDraggable(false);
	parent->getCloseButton()->setVisible(false);
	parent->setVisible(false);
	irr::gui::IGUIImage *img = env->addImage(irr::core::rect<irr::s32>((irr::u32)(rect.getWidth() / 2 * 0.05),
									(irr::u32)(rect.getHeight() * 0.05),
									(irr::u32)(rect.getWidth() / 2 * 0.95),
									(irr::u32)(rect.getHeight() * 0.95)), parent);
	img->setImage(Window::device->getVideoDriver()->getTexture(ResourceManager::getPlayerIcon(id - 1).c_str()));
	img->setScaleImage(true);
	drawPlayerBuffs(*(Bomberman *)&entity, rect, parent);
}

void HUD::drawPlayerBuffs(const Bomberman &entity,
			  const irr::core::rect<irr::s32> &rect, irr::gui::IGUIWindow *parent)
{
	irr::s32 id = entity.getTeamId() - 1;
	irr::gui::IGUIEnvironment *env = Window::device->getGUIEnvironment();
	irr::core::rect<irr::s32> iconPos((irr::s32)(rect.getWidth() / 3 * 2),
					  (irr::s32)(rect.getHeight() * 0.05),
					  (irr::s32)(rect.getWidth() / 3 * 2 + iconSize.Width),
					  (irr::s32)(rect.getHeight() * 0.05 + iconSize.Height));

	for (irr::s32 i = 0; i < 8; i++) {
		irr::core::rect<irr::s32> pos((irr::u32)(iconPos.UpperLeftCorner.X + i % 2 * iconSize.Width * 0.25),
					(irr::u32)(iconPos.UpperLeftCorner.Y + i / 2 * (iconSize.Height + iconSize.Height * 1.25)),
					(irr::u32)(iconPos.LowerRightCorner.X + i % 2 * iconSize.Width * 0.25),
					(irr::u32)(iconPos.LowerRightCorner.Y + i / 2 * (iconSize.Height + iconSize.Height * 1.25)));
		icons[id].push_back(env->addImage(pos, parent));
		icons[id][i]->setImage(env->getVideoDriver()->getTexture(
			ResourceManager::getResIcon(buffIcons[i]).c_str()));
		icons[id][i]->setScaleImage(true);
		icons[id][i]->setUseAlphaChannel(true);
		if (i < 2)
			values[id].push_back(env->addStaticText(L"0",
				irr::core::rect<irr::s32>(0, 0, 40, 40), false, true, icons[id][i]));
	}
	values[id][0]->setText(irr::core::stringw(entity.getCurrentBombs()).c_str());
	values[id][1]->setText(irr::core::stringw(entity.getRange()).c_str());
	icons[id][2]->setVisible(entity.isMount());
	icons[id][3]->setVisible(entity.isCanPassSoft());
	icons[id][4]->setVisible(entity.isCanKick());
	icons[id][5]->setVisible(entity.isRedbomb());
	icons[id][6]->setVisible(entity.isShield());
	icons[id][7]->setVisible(entity.isSkull());
}

void HUD::refresh(Scene &scene)
{
	if (scene.wasReloaded())
		reload(scene);
	for (int i = 0; i < 4; i++) {
		if (characterSheets[i])
			characterSheets[i]->setVisible(false);
	}
	if (timer)
		timer->getParent()->setVisible(false);
	gameOverCheck(scene);
	if (!scene.isInGame()) {
		if (score)
			score->setVisible(false);
		return;
	}
	for (AEntity *entity : scene.getEntities()) {
		if (entity->getType() == AEntity::BombermanType) {
			Bomberman *bomberman = (Bomberman *)entity;
			irr::s32 id = entity->getTeamId() - 1;
			characterSheets[id]->setVisible(true);
			values[id][0]->setText(irr::core::stringw(bomberman->getMaxBombs() - bomberman->getCurrentBombs()).c_str());
			values[id][1]->setText(irr::core::stringw(bomberman->getRange()).c_str());
			icons[id][2]->setVisible(bomberman->isMount());
			icons[id][3]->setVisible(bomberman->isCanPassSoft());
			icons[id][4]->setVisible(bomberman->isCanKick());
			icons[id][5]->setVisible(bomberman->isRedbomb());
			icons[id][6]->setVisible(bomberman->isShield());
			icons[id][7]->setVisible(bomberman->isSkull());
			replaceIcons(id);
		}
	}
	timer->getParent()->setVisible(true);
	if (scene.getGameMode() == GameMode::PVP) {
		timer->setText(timerFormat((300000 - scene.getTime().count()) / 1000).c_str());
		score->setVisible(false);
	}
	else {
		timer->setText(timerFormat((180000 - scene.getTime().count()) / 1000).c_str());
		score->setVisible(true);
		irr::core::stringw s = "score: ";
		s.append(std::to_string(scene.getScore()).c_str());
		score->setText(s.c_str());
	}
}

void HUD::gameOverCheck(const Scene &scene)
{
	irr::core::rect<irr::s32> res = Window::device->getVideoDriver()->getViewPort();
	auto pos = irr::core::rect<irr::s32>((irr::s32)(res.getWidth() * 0.4),
		(irr::s32)(res.getHeight() * 0.3),
		(irr::s32)(res.getWidth() * 0.6),
		(irr::s32)(res.getHeight() * 0.4));
	ResourceManager::Name status;

	if (scene.getGameMode() == GameMode::PVE)
		status = ResourceManager::Name::LOSE;
	else {
		if (scene.isDraw())
			status = ResourceManager::Name::DRAW;
		else
			status = ResourceManager::Name::WIN;
	}
	if (!gameOverImage && scene.isFinish()) {
		gameOverImage = Window::device->getGUIEnvironment()->addImage(pos);
		gameOverImage->setImage(
			Window::device->getVideoDriver()->getTexture(
				ResourceManager::getMessagePath(status,
					Window::settings.getLanguage()).c_str()));
		gameOverImage->setScaleImage(true);
		gameOverImage->setUseAlphaChannel(true);
		Window::device->getGUIEnvironment()->getRootGUIElement()->sendToBack(gameOverImage);
	}
	else if (gameOverImage && !scene.isFinish()) {
		gameOverImage->remove();
		gameOverImage = nullptr;
	}
}

void HUD::replaceIcons(irr::s32 id)
{
	irr::u32 activeBuffs = 0;

	for (irr::gui::IGUIImage *image : icons[id]) {
		irr::core::vector2d<irr::s32> topLeft
			= icons[id][0]->getRelativePosition().UpperLeftCorner;
		if (!image->isVisible())
			continue;
		image->setRelativePosition(irr::core::rect<irr::s32>((irr::u32)(topLeft.X + activeBuffs % 2 * iconSize.Width * 1.5),
			(irr::u32)(topLeft.Y + activeBuffs / 2 * (iconSize.Height + iconSize.Height * 0.25)),
			(irr::u32)(topLeft.X + activeBuffs % 2 * iconSize.Width * 1.5 + iconSize.Width),
			(irr::u32)(topLeft.Y + activeBuffs / 2 * (iconSize.Height + iconSize.Height * 0.25) + iconSize.Height)));
		activeBuffs++;
	}
}

void HUD::reload(Scene &scene)
{
	gameOverImage = nullptr;
	icons.clear();
	values.clear();
	characterSheets.clear();
	for (int i = 0; i < 4; i++) {
		icons.push_back(std::vector<irr::gui::IGUIImage *>());
		characterSheets.push_back(nullptr);
	}
	init(scene);
}

const irr::core::stringw HUD::timerFormat(irr::s32 time)
{
	std::stringstream stream;

	stream << std::setfill('0') << std::setw(2) << time / 60
		<< ":"
		<< std::setfill('0') << std::setw(2) << time % 60;
	return irr::core::stringw(stream.str().c_str());
}