/*
** EPITECH PROJECT, 2018
** Bomb
** File description:
** Declaration of Bomb
*/

#ifndef INDIE_STUDIO_BOMB_HPP
	#define INDIE_STUDIO_BOMB_HPP

#include "AEntity.hpp"

#include <chrono>

#include "SoundEngine.hpp"

class Bomb : public AEntity
{
public:
	enum Direction {
		NONE = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	Bomb(irr::core::vector3df &pos, int teamId, int range, int *, bool isRed);
	void handleEvent(Map &map, std::vector<AEntity *> &entities) override;
	const irr::core::vector3df &getPosition() const override;
	bool isAlive() const override;
	Type getType() const override;
	void explode(Map &map, std::vector<AEntity *> &entities);
	bool isExploded() const;
	void calculMovements(Map &map, std::vector<AEntity *> &vector);
	void move(const irr::core::vector3df &vec, Map &map,
		  std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions) override;
	void setDirection(Direction direction1);
	std::vector<std::pair<EventManager::Action, EventManager::InputType >> fillEventVector();
	bool checkCollisionsWithBombs(const irr::core::vector3df &pos,
				      const std::vector<AEntity *> &entities,
				      int tileSize) override;
	void draw() override;
	const std::chrono::time_point<std::chrono::high_resolution_clock> &
	getTime() const;
	void
	setTime(const std::chrono::time_point<std::chrono::high_resolution_clock> &_t);
	~Bomb() override;
	bool isMoving() const;

private:
	void explodeEntities(Map &map, std::vector<AEntity *> &entities, int tileSize, size_t xBomb, size_t yBomb);
	std::chrono::time_point<std::chrono::high_resolution_clock> _t;
	int *currentBombFromBomberman;
	int range;
	bool exploded;
	bool isRed;
	bool explosionSound;
	bool moving;
	Direction direction;
	irr::scene::IParticleSystemSceneNode *ps;
};

#endif //INDIE_STUDIO_BOMB_HPP
