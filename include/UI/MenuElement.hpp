/*
** EPITECH PROJECT, 2018
** MenuElement
** File description:
** Declaration of MenuElement
*/

#ifndef INDIE_STUDIO_MENUELEMENT_HPP
	#define INDIE_STUDIO_MENUELEMENT_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>
#include "Event.hpp"

class MenuElement
{
public:
	enum GuiElement {
		BUTTON,
		SCROLLBAR,
		CHECKBOX,
		COMBOBOX,
		SPINNERBOX
	};
	MenuElement(MenuElement::GuiElement type, const irr::core::stringw &label,
			const irr::core::stringw &text, Event::MenuItem id,
			irr::gui::IGUIElement *parent);
	~MenuElement() {};
	void draw(irr::gui::IGUIEnvironment &env, irr::core::rect<irr::s32> rect,
			irr::s32 index, irr::s32 indexMax);
	irr::core::rect<irr::s32> initSize(const irr::core::rect<irr::s32> &rect,
		irr::s32 index, irr::s32 indexMax);
	void initButton(irr::gui::IGUIButton *button,
			irr::gui::IGUIEnvironment &env);
	void initScrollbar(irr::gui::IGUIScrollBar *scrollbar);
	void initCombobox(irr::gui::IGUIComboBox *box);
	void initSpinnerBox(irr::gui::IGUISpinBox *box);
private:
	GuiElement type;
	irr::core::stringw label;
	irr::core::stringw text;
	Event::MenuItem id;
	irr::gui::IGUIElement *parent;
	irr::core::dimension2d<irr::s32> size;
};

#endif //INDIE_STUDIO_MENUELEMENT_HPP
