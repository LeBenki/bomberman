/*
** EPITECH PROJECT, 2018
** Lang
** File description:
** Declaration of Lang
*/

#ifndef INDIE_STUDIO_LANG_HPP
	#define INDIE_STUDIO_LANG_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <irrlicht/irrlicht.h>
#include "Settings.hpp"

class Lang
{
public:
	Lang();
	static void loadTexts();
	static void processLine(const std::string &line, Settings::Language lang);
	static std::string getText(const std::string &key);
	static irr::core::stringw getWText(const std::string &key);
private:
	static std::map<Settings::Language , std::map<std::string, std::string>> strings;
};

typedef std::map<std::string, std::string> LangMap;

#endif //INDIE_STUDIO_LANG_HPP
