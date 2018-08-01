/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Implementation of Scene
*/

#include "JoystickManager.hpp"
#include "Window.hpp"
#include "Scene.hpp"

Scene::Scene(irr::IrrlichtDevice *device, int mapSizeX, int mapSizeY)
	: device(device), map(MapGenerator::generate({mapSizeX, mapSizeY}, GameMode::PVP), BiomeManager::VOLCANO), reloaded(false), time(0), mapSizeX(mapSizeX), mapSizeY(mapSizeY), lastDestroy(0), hurryUp(false), finish(false), draw(false), mobCount(0), score(0), gateOpened(false)
{
	SoundEngine::playSound("Go");
	lastTime = std::chrono::high_resolution_clock::now();
	gui = device->getGUIEnvironment();
	map.draw();
	initSoundEngine();
	initSceneManager(true);
	initBombermans();
	initCamera();
	SoundEngine::playMusic(ResourceManager::getMusicByBiome(map.getBiome()));
}

Scene::Scene() : device(Window::device), gui(device->getGUIEnvironment()), reloaded(false), time(0), inGame(false), lastDestroy(0), hurryUp(false), finish(false), draw(false), mobCount(0), score(0), gateOpened(false)
{
	initSoundEngine();
	SoundEngine::playMusic("Title");
	lastTime = std::chrono::high_resolution_clock::now();
	gui = device->getGUIEnvironment();
	initTitleScene();
}

void Scene::initMap(int mapX, int mapY, BiomeManager::Name biome,
                    std::vector<std::string> rawMapContent)
{
	mapSizeX = mapX;
	mapSizeY = mapY;
	map = Map(rawMapContent, biome);
	Window::device->getSceneManager()->clear();
	map.draw();
	entities.clear();
}

void Scene::newBattleGame(int mapX, int mapY, BiomeManager::Name biome, std::vector<Event::InputType> players)
{
	gameMode = PVP;
	SoundEngine::playSound("Go");
	auto rawMapContent = MapGenerator::generate({mapX, mapY}, GameMode::PVP);
	initMap(mapX, mapY, biome, rawMapContent);
	initSceneManager(true);
	for (irr::u32 i = 0; i < players.size(); i++) {
		auto pos = irr::core::vector3df(i % 2 == 0 ? (irr::f32)(map.getTileSize()) : (irr::f32)(mapSizeX * map.getTileSize()),
						(irr::f32)map.getTileSize(), (irr::f32)(i < 2 ? map.getTileSize() : mapSizeY * map.getTileSize()) * -1);
		switch (players[i]) {
			case Event::InputType::NONE:
				break;
			case Event::InputType::AI:
				entities.push_back(new MobBomberman(pos, i + 1));
				break;
			case Event::InputType::KEYBOARD:
				entities.push_back(new Bomberman(pos, i + 1, Event::KEYBOARD));
				break;
			default:
				entities.push_back(new Bomberman(pos, i + 1, players[i]));
				break;
		}
	}
	initCamera();
	lastTime = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration<int, std::milli>(0);
	reloaded = true;
	inGame = true;
	draw = false;
	finish = false;
	hurryUp = false;
	lastDestroy = 0;
	SoundEngine::setMusicVolume(0.5);
	SoundEngine::playMusic(ResourceManager::getMusicByBiome(biome));
}

void Scene::newCampaignGame()
{
	mobCount = 0;
	score = 0;
	SoundEngine::playSound("Go");
	gameMode = PVE;
	auto biome = BiomeManager::getRandomBiome(1, 8);
	auto rawMapContent = MapGenerator::generate({15, 17},
		GameMode::PVE);
	initMap(15, 17, biome, rawMapContent);
	initSceneManager(true);
	auto pos = irr::core::vector3df((irr::f32)map.getTileSize(), (irr::f32)map.getTileSize(),
	                                (irr::f32)(map.getTileSize()) * -1);
	entities.push_back(new Bomberman(pos, 1, Event::KEYBOARD));
	initMobs(rawMapContent);
	initCamera();
	lastTime = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration<int, std::milli>(0);
	reloaded = true;
	inGame = true;
	draw = false;
	finish = false;
	hurryUp = false;
	lastDestroy = 0;
	SoundEngine::setMusicVolume(0.5);
	SoundEngine::playMusic(ResourceManager::getMusicByBiome(biome));
}

void Scene::initTitleScene()
{
	irr::scene::ISceneManager *smgr = device->getSceneManager();

	irr::core::vector3df pos(0, 0, 0);
	entities.push_back(new Bomberman(pos, 1, Event::KEYBOARD));
	pos = irr::core::vector3df(0, 20, -40);
	camera = smgr->addCameraSceneNode(nullptr, pos, irr::core::vector3df(0, 0, 0));
	smgr->addLightSceneNode(nullptr, pos, irr::video::SColor(255, 255, 255, 255), 600.0f);
	pos = irr::core::vector3df(0, 20, 40);
	smgr->addLightSceneNode(nullptr, pos, irr::video::SColor(100, 255, 255, 255), 600.0f);
	finish = false;
	draw = false;
	gameMode = GameMode::PVP;
}

void Scene::initCamera()
{
	irr::scene::ISceneManager *smgr = device->getSceneManager();

	camera = smgr->addCameraSceneNode(nullptr, irr::core::vector3df(0, 30, -40),
						irr::core::vector3df(0, 5, 0));
	camera->setPosition(irr::core::vector3df((irr::f32)(map.getWidth() - map.getTileSize()) / 2,
						 static_cast<irr::f32>((irr::f32)map.getHeight() * 0.8),
						 (irr::f32)(map.getHeight() * 0.8) * -1));
	camera->setTarget(irr::core::vector3df((irr::f32)(map.getWidth() - map.getTileSize()) / 2,
					       0, (irr::f32)map.getHeight() / 2 * -1));
	camera->setFarValue(100000.0f);
	for (int i = 0; i < 4; i++)
		cameras.push_back(nullptr);
	for (AEntity *entity : entities) {
		if (entity->getType() == AEntity::BombermanType) {
			irr::core::vector3df pos(entity->getPosition().X, 200, entity->getPosition().Z - 100);
			cameras[entity->getTeamId() - 1] = smgr->addCameraSceneNode(nullptr, pos, entity->getPosition());
			cameras[entity->getTeamId() - 1]->setFarValue(100000.0f);
		}
	}
}

void Scene::initSceneManager(bool shadows)
{
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	auto light1 = smgr->addLightSceneNode(nullptr, irr::core::vector3df((irr::f32)map.getWidth() / 2,
		(irr::f32)500, (irr::f32)map.getHeight() / 2 * -1),
		irr::video::SColorf(0.6f, 0.6f, 0.7f, 0.8f),
		static_cast<irr::f32>(300 + map.getHeight() * 0.4));
	auto light2 = smgr->addLightSceneNode(nullptr, irr::core::vector3df(-500, 400, 100),
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),
		static_cast<irr::f32>(400 + map.getHeight() * 0.7));
	if (!shadows) {
		light1->enableCastShadow(false);
		light2->enableCastShadow(false);
	}
	ambientLights.clear();
	ambientLights.push_back(light1);
	ambientLights.push_back(light2);
	smgr->setShadowColor(irr::video::SColor(100,0,0,0));
}

void Scene::initMobs(std::vector<std::string> rawMapContent)
{
	auto tileSize = (irr::f32)map.getTileSize();
	for (size_t y = 0 ; y < rawMapContent.size() ; y++) {
		for (size_t x = 0 ; x < rawMapContent[y].size() ; x++) {
			if (rawMapContent[y][x] == 'M') {
				irr::core::vector3df pos(x * tileSize, tileSize,
				                         tileSize * y * -1);
				entities.push_back(
					new Mob(pos, 2, map.getBiome()));
				mobCount++;
			}
		}
	}
}

void Scene::initBombermans()
{
	auto tileSize = (irr::f32)map.getTileSize();
	irr::core::vector3df pos(tileSize, tileSize, tileSize * -1);
	entities.push_back(new Bomberman(pos, 1, Event::KEYBOARD));
	irr::core::vector3df pos2(tileSize * mapSizeX, tileSize, tileSize * -1);
	entities.push_back(new MobBomberman(pos2, 2));
	irr::core::vector3df pos3(tileSize, tileSize, tileSize * mapSizeY * -1);
	entities.push_back(new Bomberman(pos3, 3, Event::KEYBOARD));
	irr::core::vector3df pos4(tileSize * mapSizeX, tileSize, tileSize * mapSizeY * -1 - 2);
	entities.push_back(new Bomberman(pos4, 4, Event::KEYBOARD));
}

void Scene::initSoundEngine()
{
	SoundEngine::initSoundEngine();
}

irr::scene::ICameraSceneNode *Scene::getCamera() const
{
	return camera;
}

void Scene::setCamera(irr::scene::ICameraSceneNode *camera)
{
	Scene::camera = camera;
}

const std::vector<AEntity *> &Scene::getEntities() const
{
	return entities;
}

void Scene::setEntities(const std::vector<AEntity *> &entities)
{
	Scene::entities = entities;
}

void Scene::destroyDeadEntities()
{
	unsigned long size = entities.size();

	for (unsigned long i = 0; i < size; ++i) {
		if (!entities[i]->isAlive()) {
			if (entities[i]->getType() == AEntity::Type::MOB) {
				SoundEngine::playSound("Disease");
				mobCount--;
				score += 800;
			}
			delete entities[i];
			entities.erase(entities.begin() + i);
			destroyDeadEntities();
			break;
		}
	}
}

void Scene::processHurryUp()
{
	int newOne = 0;

	if (getTime().count() > 120000) {
		if (!hurryUp) {
			SoundEngine::playSound("HurryUp");
			SoundEngine::speedUpMusic();
			hurryUp = true;
		}
		newOne = getTime().count();
		if (newOne - lastDestroy > 500 && map.canDestroy()) {
			map.startDestruction(entities);
			lastDestroy = newOne;
		}
		else
			map.refreshBlocks(entities);
	}
}

bool Scene::refreshEntities() {
	int bombermanNum = 0;

	unsigned long size = entities.size();
	for (unsigned long i = 0; i < size; ++i) {
		if (entities[i]->getType() == AEntity::BombermanType)
			++bombermanNum;
		entities[i]->handleEvent(map, entities);
	}
	if (!bombermanNum) {
		if (gameMode == PVP)
			draw = true;
		finish = true;
	}
	if (gameMode == PVP && (bombermanNum == 1 || bombermanNum == 0)) {
		finish = true;
		return true;
	}
	return false;
}

void Scene::openGate()
{
	SoundEngine::playSound("Door");
	auto &tiles = map.getTiles();

	for (auto &tileLine : tiles) {
		for (auto &tile : tileLine) {
			if (tile->getType() == ITile::Type::GATE) {
				auto gate = (TileGate *)(tile.get());
				gate->open();
				gateOpened = true;
			}
		}
	}
}

bool Scene::playerIsOnGate()
{
	for (auto &entity : entities) {
		if (entity->getType() == AEntity::Type::BombermanType) {
			auto player = (Bomberman *)entity;
			return player->isTookDoor();
		}
	}
	return false;
}

void Scene::resetPlayer()
{

	for (auto &entity : entities) {
		if (entity->getType() == AEntity::Type::BombermanType) {
			auto player = (Bomberman *)entity;
			auto pos = irr::core::vector3df((irr::f32)map.getTileSize(),
				player->isMount() ? (irr::f32)map.getTileSize() : (irr::f32)map.getTileSize() - 20,
				                        (irr::f32)(map.getTileSize()) * -1);
			player->setPosition(pos);
			player->setTookDoor(false);
		}
	}
}

void Scene::nextCampaignLevel()
{
	gateOpened = false;
	auto remainingSeconds = 300 - std::chrono::duration_cast<std::chrono::seconds> (time).count();
	score += (size_t)remainingSeconds * 50;
	time = std::chrono::duration<int, std::milli> (0);
	map.clearFallingBlocks();
	SoundEngine::playSound("Go");
	auto tileSize = map.getTileSize();
	auto mapContent = MapGenerator::generate({mapSizeX, mapSizeY},
		GameMode::PVE);
	auto newBiome = map.getBiome();
	while (newBiome == map.getBiome())
		newBiome = BiomeManager::getRandomBiome(1, 8);
	map = Map(mapContent, newBiome, tileSize);
	map.draw();
	resetPlayer();
	initMobs(mapContent);
	SoundEngine::playMusic(ResourceManager::getMusicByBiome(newBiome));
}

size_t Scene::getScore() const
{
	return score;
}

void Scene::refresh(Event &event, bool pause, bool shadows, bool splitScreen)
{
	auto now = std::chrono::high_resolution_clock::now();
	EventManager::refresh(event);
	JoystickManager::refresh(event);

	if (!pause) {
		if (gameMode == PVE && !gateOpened && !mobCount) {
			openGate();
		}
		if (gameMode == PVE && playerIsOnGate()) {
			nextCampaignLevel();
		}
		enableAnimations();
		if (!finish) {
			time += std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - lastTime.time_since_epoch());
		}
		moveCamera();
		if (!finish)
			if (refreshEntities() && !draw) {
				makeLastPlayerDab();
			}
		map.refresh();
		destroyDeadEntities();
		if (!finish)
			processHurryUp();
		else
			finishScene();
	}
	else if (inGame) {
		disableAnimations();
		setBombsOnPause();
	}
	display(shadows, splitScreen);
	gui->drawAll();
	lastTime = now;
}

void Scene::display(bool shadows, bool splitScreen)
{
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::core::rect<irr::s32> res = driver->getViewPort();
	irr::core::vector3df pos;
	std::vector<int> teams;

	for (irr::scene::ILightSceneNode *light : ambientLights)
		light->enableCastShadow(shadows);
	for (AEntity *entity : entities) {
		if (std::find(teams.begin(), teams.end(), entity->getTeamId()) == teams.end())
			teams.push_back(entity->getTeamId());

	}
	if (splitScreen && cameras.size() > 1) {
		for (AEntity *entity : entities) {
			if (entity->getType() == AEntity::BombermanType) {
				irr::f32 ratio = teams.size() > 2 ? (irr::f32)1 : (irr::f32)2;
				driver->setViewPort(irr::core::rect<irr::s32>(
					(irr::s32)(res.UpperLeftCorner.X + res.getWidth() / (cameras.size() / 2) * ((entity->getTeamId() - 1) % 2)),
					(irr::s32)(res.UpperLeftCorner.Y + res.getHeight() / (cameras.size() / 2) * ((entity->getTeamId() - 1) / 2)),
					(irr::s32)(res.UpperLeftCorner.X + res.getWidth() / (cameras.size() / 2) * ((entity->getTeamId() - 1) % 2 + 1)),
					(irr::s32)(res.UpperLeftCorner.Y + res.getHeight() / (cameras.size() / 2) * ratio * ((entity->getTeamId() - 1) / 2 + 1))));
				pos = entity->getPosition();
				cameras[entity->getTeamId() - 1]->setTarget(pos);
				pos.Y += 100;
				pos.Z -= 50;
				cameras[entity->getTeamId() - 1]->setPosition(pos);
				cameras[entity->getTeamId() - 1]->setAspectRatio((irr::f32)driver->getViewPort().getWidth() / driver->getViewPort().getHeight());
				smgr->setActiveCamera(cameras[entity->getTeamId() - 1]);
				smgr->drawAll();
			}
		}
	}
	else {
		smgr->setActiveCamera(camera);
		smgr->drawAll();
	}
	driver->setViewPort(res);
}

void Scene::setBombsOnPause()
{
	auto now = std::chrono::high_resolution_clock::now();
	for (AEntity *entity : entities) {
		if (entity->getType() == AEntity::BombType) {
			Bomb *bomb = (Bomb *)entity;
			bomb->setTime(bomb->getTime() + std::chrono::nanoseconds(now - lastTime));
		}
	}
}

void Scene::resetTimer()
{
	lastTime = std::chrono::high_resolution_clock::now();
}

void Scene::moveCamera()
{
	std::vector<std::pair<EventManager::Action, EventManager::InputType>>
		actions = EventManager::getEvents();

	auto oldPosition = camera->getPosition();
	for (auto &act : actions) {
		if (act.second != EventManager::PRESSED)
			continue;
		switch (act.first) {
			case EventManager::CAMERA_YUP:
				oldPosition.Y += 1;
				break;
			case EventManager::CAMERA_YDOWN:
				oldPosition.Y -= 1;
				break;
			case EventManager::CAMERA_XUP:
				oldPosition.X += 1;
				break;
			case EventManager::CAMERA_XDOWN:
				oldPosition.X -= 1;
				break;
			case EventManager::CAMERA_ZDOWN:
				oldPosition.Z -= 1;
				break;
			case EventManager::CAMERA_ZUP:
				oldPosition.Z += 1;
				break;
			default:
				break;
		}
	}
	camera->setPosition(oldPosition);
}

void Scene::reload()
{
	Window::device->getSceneManager()->clear();
	cameras.clear();
	if (inGame) {
		map.draw();
		for (auto entity : entities)
			entity->draw();
		initSceneManager(Window::settings.isShadows());
		initCamera();
	}
	else {
		initTitleScene();
	}
	gui = device->getGUIEnvironment();
	reloaded = true;
}

void Scene::clear()
{
	for (AEntity *entity : entities)
		delete entity;
	entities.clear();
	cameras.clear();
	ambientLights.clear();
	map = Map();
	Window::device->getSceneManager()->clear();
}

void Scene::setDevice(irr::IrrlichtDevice *device)
{
	Scene::device = device;
}

void Scene::enableAnimations()
{
	for (AEntity *entity : entities)
		entity->toggleAnimation(true);
}

void Scene::disableAnimations()
{
	for (AEntity *entity : entities)
		entity->toggleAnimation(false);
}

bool Scene::wasReloaded()
{
	if (reloaded) {
		reloaded = false;
		return true;
	}
	return false;
}

const std::chrono::duration<int, std::milli> &Scene::getTime() const
{
	return time;
}

bool Scene::isInGame() const
{
	return inGame;
}

void Scene::setReloaded(bool state)
{
	reloaded = state;
}

Map &Scene::getMap()
{
	return map;
}

void Scene::setInGame(bool inGame)
{
	Scene::inGame = inGame;
}

void Scene::finishScene()
{
	auto pos = camera->getPosition();

	if (pos.Y > 50)
	{
		pos.Y -= 1;
		camera->setPosition(pos);
	}
	if (!draw)
	{
		for (auto &entity : entities)
		{
			if (entity->getType() == AEntity::BombermanType)
				camera->setTarget(entity->getPosition());
		}
	}
}

void Scene::makeLastPlayerDab()
{
	for (auto &entity : entities) {
		if (entity->getType() == AEntity::BombermanType) {
			Bomberman *bomberman = (Bomberman *)entity;
			bomberman->dab();
		}
	}
}
GameMode Scene::getGameMode() const
{
	return gameMode;
}

bool Scene::isFinish() const
{
	return finish;
}

bool Scene::isDraw() const
{
	return draw;
}

void Scene::setTime(irr::s32 ms)
{
	time = std::chrono::duration<int, std::milli>(ms);
}
