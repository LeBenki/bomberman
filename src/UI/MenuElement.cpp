/*
** EPITECH PROJECT, 2018
** MenuElement
** File description:
** Implementation of MenuElement
*/

#include <Settings.hpp>
#include <Lang.hpp>
#include <ResourceManager.hpp>
#include "MenuElement.hpp"

MenuElement::MenuElement(MenuElement::GuiElement type,
			const irr::core::stringw &label,
			const irr::core::stringw &text, Event::MenuItem id,
			irr::gui::IGUIElement *parent)
	: type(type), label(label), text(text), id(id), parent(parent)
{

}

void MenuElement::draw(irr::gui::IGUIEnvironment &env,
			irr::core::rect<irr::s32> rect, irr::s32 index,
			irr::s32 indexMax)
{
	irr::core::rect<irr::s32> size;

	switch (type) {
		case BUTTON:
			size = initSize(rect, index, indexMax);
			initButton(env.addButton(size, parent, id, label.c_str()), env);
			break;
		case SCROLLBAR:
			size = initSize(rect, index, indexMax);
			initScrollbar(env.addScrollBar(true, size, parent, id));
			break;
		case CHECKBOX:
			size = initSize(rect, index, indexMax);
			env.addCheckBox(false, size, parent, id, label.c_str());
			break;
		case COMBOBOX:
			size = initSize(rect, index, indexMax);
			initCombobox(env.addComboBox(size, parent, id));
			break;
		case SPINNERBOX:
			size = initSize(rect, index, indexMax);
			initSpinnerBox(env.addSpinBox(L"", size, true, parent, id));
			break;
		default:
			return;
	}
	if (!text.empty())
		env.addStaticText(text.c_str(), irr::core::rect<irr::s32>(
			static_cast<irr::s32>(rect.getWidth() / 2 + rect.getWidth() * 0.15),
				size.LowerRightCorner.Y - size.getHeight(),
			rect.getWidth(),
			size.LowerRightCorner.Y),
			false, true, parent)
			->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

irr::core::rect<irr::s32> MenuElement::initSize(const irr::core::rect<irr::s32> &rect,
						irr::s32 index, irr::s32 indexMax)
{
	switch (type) {
		case BUTTON:
			size = irr::core::dimension2d<irr::s32>(
				static_cast<const irr::s32 &>(rect.getWidth() * 0.30),
				static_cast<const irr::s32 &>(rect.getHeight() * 0.25 / (indexMax * 0.75)));
			return {static_cast<irr::s32>(rect.getWidth() / 2 - size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 - size.Height / 2),
				static_cast<irr::s32>(rect.getWidth() / 2 + size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 + size.Height / 2)};
		case SCROLLBAR:
			size = irr::core::dimension2d<irr::s32>(
				static_cast<const irr::s32 &>(rect.getWidth() * 0.25),
				static_cast<const irr::s32 &>(rect.getHeight() * 0.25 / (indexMax * 0.75)));
			return {static_cast<irr::s32>(rect.getWidth() / 2 - size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 - size.Height / 2),
				static_cast<irr::s32>(rect.getWidth() / 2 + size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 + size.Height / 2)};
		case CHECKBOX:
			size = irr::core::dimension2d<irr::s32>(
				static_cast<const irr::s32 &>(rect.getWidth() * 0.25),
				static_cast<const irr::s32 &>(rect.getHeight() * 0.25 / (indexMax * 0.75)));
			return {static_cast<irr::s32>(rect.getWidth() / 2 - size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 - size.Height / 2),
				static_cast<irr::s32>(rect.getWidth() / 2 + size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 + size.Height / 2)};
		case COMBOBOX:
			size = irr::core::dimension2d<irr::s32>(
				static_cast<const irr::s32 &>(rect.getWidth() * 0.25),
				static_cast<const irr::s32 &>(rect.getHeight() * 0.25 / (indexMax * 0.75)));
			return {static_cast<irr::s32>(rect.getWidth() / 2 - size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 - size.Height / 2),
				static_cast<irr::s32>(rect.getWidth() / 2 + size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 + size.Height / 2)};
		case SPINNERBOX:
			size = irr::core::dimension2d<irr::s32>(
				static_cast<const irr::s32 &>(rect.getWidth() * 0.25),
				static_cast<const irr::s32 &>(rect.getHeight() * 0.25 / (indexMax * 0.75)));
			return {static_cast<irr::s32>(rect.getWidth() / 2 - size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 - size.Height / 2),
				static_cast<irr::s32>(rect.getWidth() / 2 + size.Width / 2),
				static_cast<irr::s32>(rect.getHeight() / 2 - ((float)indexMax / 2 - index - 0.5) * size.Height * 2 + size.Height / 2)};
		default:
			return irr::core::rect<irr::s32>(0, 0, 0, 0);
	}
}

void MenuElement::initButton(irr::gui::IGUIButton *button,
				irr::gui::IGUIEnvironment &env)
{
	button->setDrawBorder(false);
	button->setImage(env.getVideoDriver()->getTexture(ResourceManager::getMenuPath(ResourceManager::MENU_BUTTON).c_str()));
	button->setScaleImage(true);
	button->setUseAlphaChannel(true);
	button->setPressedImage(env.getVideoDriver()->getTexture(ResourceManager::getMenuPath(ResourceManager::MENU_BUTTON_PRESSED).c_str()));
}

void MenuElement::initScrollbar(irr::gui::IGUIScrollBar *scrollbar)
{
	switch (id) {
		case Event::MUSIC_VOLUME:
			scrollbar->setMin(0);
			scrollbar->setMax(100);
			break;
		case Event::FX_VOLUME:
			scrollbar->setMin(0);
			scrollbar->setMax(100);
			break;
		default:
			return;
	}
}

void MenuElement::initCombobox(irr::gui::IGUIComboBox *box)
{

	if (id == Event::PLAYER1 || id == Event::PLAYER2
		|| id == Event::PLAYER3 || id == Event::PLAYER4) {
		box->addItem(Lang::getWText("disabled").c_str());
		box->addItem(Lang::getWText("ai").c_str());
		box->addItem(Lang::getWText("keyboard").c_str());
		box->addItem(Lang::getWText("controller").c_str());
	}
	switch (id) {
		case Event::RESOLUTION:
			box->setText(L"RES");
			for (irr::core::dimension2d<irr::u32> res : Settings::resolutions) {
				box->addItem(irr::core::stringw(irr::core::stringw(std::to_string(res.Width).c_str())
					+ "x" + irr::core::stringw(std::to_string(res.Height).c_str()).c_str()).c_str());
			}
			break;
		case Event::GRAPHICS:
			box->setText(L"GRAPHICS");
			box->addItem(Lang::getWText("graphicsLow").c_str());
			box->addItem(Lang::getWText("graphicsMedium").c_str());
			box->addItem(Lang::getWText("graphicsUltra").c_str());
			break;
		case Event::LANGUAGE:
			box->setText(L"LANG");
			box->addItem(Lang::getWText("en").c_str());
			box->addItem(Lang::getWText("fr").c_str());
			box->addItem(Lang::getWText("es").c_str());
			break;
		case Event::BIOME:
			box->setText(L"BIOME");
			box->addItem(Lang::getWText("random").c_str());
			box->addItem(Lang::getWText("beach").c_str());
			box->addItem(Lang::getWText("jungle").c_str());
			box->addItem(Lang::getWText("factory").c_str());
			box->addItem(Lang::getWText("volcano").c_str());
			box->addItem(Lang::getWText("ice").c_str());
			box->addItem(Lang::getWText("retro").c_str());
			box->addItem(Lang::getWText("city").c_str());
			box->addItem(Lang::getWText("mushroom").c_str());
			break;
		default:
			return;
	}
}

void MenuElement::initSpinnerBox(irr::gui::IGUISpinBox *box)
{
	switch (id) {
		case Event::MAP_WIDTH:
			box->setRange(13, 100);
			box->setValue(13);
			break;
		case Event::MAP_HEIGHT:
			box->setRange(11, 100);
			box->setValue(11);
			break;
		default:
			break;
	}
}