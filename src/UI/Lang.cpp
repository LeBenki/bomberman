/*
** EPITECH PROJECT, 2018
** Lang
** File description:
** Implementation of Lang
*/

#include "Window.hpp"
#include "Lang.hpp"

std::map<Settings::Language, LangMap> Lang::strings;

Lang::Lang()
{
}

void Lang::loadTexts()
{
	std::ifstream file(ResourceManager::getLangPath());
	Settings::Language lang = Settings::ENGLISH;
	std::string line;

	if (!file.is_open())
		return;
	while (getline(file, line)) {
		if (line == "[en]")
			lang = Settings::ENGLISH;
		else if (line == "[fr]")
			lang = Settings::FRENCH;
		else if (line == "[es]")
			lang = Settings::SPANISH;
		else
			processLine(line, lang);
	}
}

void Lang::processLine(const std::string &line, Settings::Language lang)
{
	std::string key;
	std::string value;
	LangMap &texts = strings[lang];
	std::istringstream f(line);

	if (!getline(f, key, '=') || !key.size())
		return;
	if (!getline(f, value) || !value.size())
		return;
	texts[key] = value;
}

std::string Lang::getText(const std::string &key)
{
	LangMap &texts = strings[Window::settings.getLanguage()];

	if (!texts.count(key))
		return "NULL";
	return texts[key];
}

irr::core::stringw Lang::getWText(const std::string &key)
{
	LangMap &texts = strings[Window::settings.getLanguage()];

	if (!texts.count(key))
		return irr::core::stringw("NULL").c_str();
	else
		return irr::core::stringw(texts[key].c_str());
}
