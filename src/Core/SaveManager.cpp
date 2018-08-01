/*
** EPITECH PROJECT, 2018
** IndieExceptions
** File description:
** Implementation of SaveManager
*/

#include <SaveManager.hpp>

void splitString(const std::string& str,
                 std::vector<std::string> &strings, char sep)
{
	std::stringstream ss(str);
	std::string word;

	while (std::getline(ss, word, sep)) {
	strings.push_back(word);
	}
}

std::string vector3dfToFormat(irr::core::vector3df vector)
{
	return "(" + std::to_string(vector.X) + "," + std::to_string(vector.Y)
	       + "," + std::to_string(vector.Z) + ")";
}
irr::core::vector3df formatToVector3df(const std::string& str)
{
	irr::core::vector3df v;
	std::vector<std::string> strings;

	auto sstr = str.substr(1, str.length() - 2);
	splitString(sstr, strings, ',');
	v.X = (irr::f32)std::stoi(strings.at(0));
	v.Y = (irr::f32)std::stoi(strings.at(1));
	v.Z = (irr::f32)std::stoi(strings.at(2));
	return v;
}

void saveMap(std::ofstream &saveFile, const Map &map)
{
	saveFile << "[B]" << map.getBiome() << std::endl;
	saveFile << "[T]" << std::to_string(map.getTileSize()) << std::endl;
	auto strMap = map.getMapInLuaFormat();
	for (auto &line : strMap) {
		for (auto &c : line) {
			if (c == 'F' || c == 'B')
				c = ' ';
		}
		saveFile << "[M]" << line << std::endl;
	}
}

void saveEntities(std::ofstream &saveFile,
                  const std::vector<AEntity *> &entities)
{
    for (const auto &entity : entities)
        if (entity->getType() == AEntity::Type::BombermanType) {
            saveFile << "[E]" <<
                     vector3dfToFormat(entity->getPosition()) << ";" <<
                     entity->getTeamId() << ";" <<
                     entity->serialize() << std::endl;
        }
}

void SaveManager::saveScene(Scene &scene)
{
	std::ofstream saveFile;
	try {
		saveFile.open(ResourceManager::getSavePath());
		if (saveFile.is_open()) {
			saveFile << "[t]" << scene.getTime().count() << std::endl;
			saveMap(saveFile, scene.getMap());
			saveEntities(saveFile, scene.getEntities());
			saveFile.close();
		} else {
			throw std::invalid_argument("Error occured when opening save file!");
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

void loadMap(Map &map, const std::vector<std::string> &fileContent)
{
	std::vector<std::string> mapContent;
	irr::s32 tileSize = -1;
	BiomeManager::Name biome = BiomeManager::Name::JUNGLE;

	for (const auto &line: fileContent) {
		std::string prefix = line.substr(0, 3);
		std::string content = line.substr(3, line.length() - 3);
		if (prefix == "[M]") {
			mapContent.push_back(content);
		} else if (prefix == "[B]") {
			biome = BiomeManager::Name(atoi(content.c_str()));
		} else if (prefix == "[T]") {
			tileSize = atoi(content.c_str());
		}
	}
	if (!mapContent.empty() && tileSize != -1) {
		map.setBiome(biome);
		map.setTileSize(tileSize);
		map << mapContent;
		map.draw();
	} else {
		throw std::invalid_argument("Error with map save format!");
	}
}

void loadEntity(std::vector<AEntity *> &entities, const std::string &line)
{
	std::vector<std::string> strings;
	splitString(line.substr(3, line.length() - 3), strings, ';');
	if (strings.size() != 13) {
		std::string error = "Error occured when loading entities! Expected attributes, got " +
		                    std::to_string(strings.size());
		throw std::invalid_argument(error);
	}
	auto pos = formatToVector3df(strings.at(0));
	if (strings.at(10) == "False")
		pos.Y += 20;
	auto inputMode = Event::InputType(stoi(strings.at(12)));
	auto bomberman = inputMode == Event::InputType::AI
		? new MobBomberman (pos, std::stoi(strings.at(1)))
		: new Bomberman (pos, std::stoi(strings.at(1)), inputMode);
	bomberman->deserialize(strings);
	entities.push_back(bomberman);
}

void destroyEntities(std::vector<AEntity *> &entities)
{
	unsigned long size = entities.size();

	for (unsigned long i = 0; i < size; ++i) {
		delete entities[i];
		entities.erase(entities.begin() + i);
		destroyEntities(entities);
		break;
	}
}

void loadEntities(std::vector<AEntity *> &entities,
                  const std::vector<std::string> &fileContent)
{
	destroyEntities(entities);

	for (const auto &line: fileContent) {
		if (line.substr(0, 3) == "[E]") {
			loadEntity(entities, line);
		}
	}
}

void loadTime(Scene &scene, const std::vector<std::string> &fileContent)
{
	for (const auto &line: fileContent) {
		if (line.substr(0, 3) == "[t]") {
			irr::s32 time = atoi(line.substr(3, line.size() - 3).c_str());
			scene.setTime(time);
		}
	}
}

void SaveManager::loadScene(const std::string &filename, Scene &scene)
{
	std::vector<std::string> fileContent;
	std::ifstream saveFile(filename);
	std::string line;

	try {
		if (saveFile.is_open()) {
			while (std::getline(saveFile, line)) {
				fileContent.push_back(line);
			}
			loadTime(scene, fileContent);
			loadMap(scene.getMap(), fileContent);
			loadEntities(const_cast<std::vector<AEntity *>&>(scene.getEntities()), fileContent);
			saveFile.close();
		} else {
			throw std::invalid_argument("Error occured when opening save file!");
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	SoundEngine::playMusic(ResourceManager::getMusicByBiome(scene.getMap().getBiome()));
}