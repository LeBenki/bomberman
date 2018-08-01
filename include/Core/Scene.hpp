/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Declaration of Scene
*/

#ifndef CPP_INDIE_STUDIO_SCENE_HPP
	#define CPP_INDIE_STUDIO_SCENE_HPP

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include <vector>
#include <memory>

#include "AEntity.hpp"
#include "SoundEngine.hpp"
#include "Bomberman.hpp"
#include "Map.hpp"
#include "Settings.hpp"
#include "Mob.hpp"
#include "MobBomberman.hpp"
#include "MapGenerator.hpp"
#include "IndieExceptions.hpp"
#include "SoundEngine.hpp"
# include "GameMode.hpp"

class Scene
{
public:
	explicit Scene(irr::IrrlichtDevice *device, int mapSizeX = 13, int mapSizeY = 11);
	Scene();
	void refresh(Event &event, bool pause, bool shadows, bool splitScreen);
	void display(bool shadows, bool splitScreen);
	void resetTimer();
	void destroyDeadEntities();
	irr::scene::ICameraSceneNode *getCamera() const;
	void setDevice(irr::IrrlichtDevice *device);
	void setCamera(irr::scene::ICameraSceneNode *camera);
	const std::vector<AEntity *> &getEntities() const;
	void setEntities(const std::vector<AEntity *> &entities);
	void moveCamera();
	void initMap(int mapX, int mapY, BiomeManager::Name biome,
	             std::vector<std::string> rawMapContent);
        void initSoundEngine();
	void initCamera();
	void initSceneManager(bool shadows);
	void initBombermans();
	void initMobs(std::vector<std::string> rawMapContent);
	void reload();
	void clear();
	void enableAnimations();
	void disableAnimations();
	bool wasReloaded();
	void setReloaded(bool reloaded);
	void setBombsOnPause();
	void newBattleGame(int mapX, int mapY, BiomeManager::Name, std::vector<Event::InputType> players);
	void newCampaignGame();
	const std::chrono::duration<int, std::milli> &getTime() const;
	void initTitleScene();
	Map &getMap();
	void setInGame(bool inGame);
	bool isInGame() const;
	void processHurryUp();
	bool refreshEntities();
	void openGate();
	bool playerIsOnGate();
	void nextCampaignLevel();
	void resetPlayer();
	void finishScene();
	void makeLastPlayerDab();
	GameMode getGameMode() const;
	bool isFinish() const;
	bool isDraw() const;
	size_t getScore() const;
	void setTime(irr::s32 ms);

private:
	irr::IrrlichtDevice *device;
	irr::scene::ICameraSceneNode *camera;
	std::vector<irr::scene::ICameraSceneNode *> cameras;
	std::vector<irr::scene::ILightSceneNode *> ambientLights;
	std::vector<AEntity *> entities;
	irr::gui::IGUIEnvironment *gui;
	Map map;
	bool reloaded;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
	std::chrono::duration<int, std::milli> time;
	int mapSizeX;
	int mapSizeY;
	bool inGame;
	int lastDestroy;
	bool hurryUp;
	bool finish;
	bool draw;
	size_t mobCount;
	GameMode gameMode;
	size_t score;
	bool gateOpened;
};

#endif //CPP_INDIE_STUDIO_SCENE_HPP
