/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Declaration of Player
*/

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
	#define CPP_INDIE_STUDIO_PLAYER_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "EventManager.hpp"
#include "AEntity.hpp"
#include "Bomb.hpp"
#include "Mount.hpp"

class Bomberman : public AEntity
{
public:
	explicit Bomberman(irr::core::vector3df &pos, int teamId, Event::InputType type);
	void handleEvent(Map &map, std::vector<AEntity *> &entities) override;
	void doBombermanThings(std::vector<std::pair<EventManager::Action, EventManager::InputType >> events, Map &map, std::vector<AEntity *> &entities);
	void putDownBomb(const Map &map, std::vector<AEntity *> &entities);
	void move(const irr::core::vector3df &, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions) override;
	void setAnimationsData() override;
	void kickBombs(const irr::core::vector3df &pos,
		       const std::vector<AEntity *> &entities, int tileSize);
	Bomb::Direction calculDirection(size_t playerX, size_t playerY, size_t oldPlayerX, size_t oldPlayerY);
	bool calculAnimations(const irr::core::vector3df &oldPositions) override;
	void draw() override;
	void kill() override;
	~Bomberman() override;
	virtual std::string serialize() override;
	virtual void deserialize(const std::vector<std::string> &stats) override;
	bool checkCollisionsWithMobs(const std::vector<AEntity *> &entities);
	int getMaxBombs() const;
	int getRange() const;
	bool isCanPassSoft() const;
	bool isCanKick() const;
	int getCurrentBombs() const;
	bool isShield() const;
	bool isRedbomb() const;
	bool isMount() const;
	void processSkull(std::vector<std::pair<EventManager::Action, EventManager::InputType>> &events);
	bool checkCollisionsWithBombermans(std::vector<AEntity *> &entities);
	bool isTookDoor() const;
	void setTookDoor(bool tookDoor);
	void dab();
	virtual void setPosition(const irr::core::vector3df &);
	void shieldFX();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> dieLastTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> skullLastTime;
	Mount *monture;
	int zUp;
	Event::InputType inputType;
protected:
	int maxBombs;
	int range;
	bool canPassSoft;
	bool canKick;
	bool canThrow;
	int currentBombs;
	bool curse;
	bool shield;
	bool redbomb;
	bool mount;
	bool skull;
	bool tookDoor;
public:
	void setMount();
	void setRedbomb();
	void setShield();
	void setCanKick();
	void passSoft();
	void bombsUp();
	void rangeUp();
	void speedUp();
	void rangeMax();
	bool setSkull();
	bool isSkull() const;
	irr::scene::IParticleSystemSceneNode *ps;
};

#endif //CPP_INDIE_STUDIO_PLAYER_HPP
