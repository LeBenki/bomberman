/*
** EPITECH PROJECT, 2018
** AEntity
** File description:
** Declaration of AEntity
*/

#ifndef CPP_INDIE_STUDIO_AENTITY_HPP
	#define CPP_INDIE_STUDIO_AENTITY_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <irrlicht/irrlicht.h>
#include <string>
#include "ResourceManager.hpp"
#include "EventManager.hpp"
#include "Event.hpp"
#include "Map.hpp"

class AEntity
{
public:
	enum Status {
		IDLE,
		RUNNING,
		DABBING,
	};
	enum Type {
		BombermanType,
		BombType,
		MOUNT,
		MOB
	};
	explicit AEntity(ResourceManager::Name resName,
			irr::core::vector3df &pos,
			int teamId, Type type, bool isMD2 = true);
	virtual const irr::core::vector3df &getPosition() const;
	virtual void setPosition(const irr::core::vector3df &);
	virtual void move(const irr::core::vector3df &, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions);
	virtual void handleEvent(Map &map, std::vector<AEntity *> &entities) = 0;
	virtual void setAnimationsData();
	double getSpeed() const;
	void setSpeed(irr::f32 speed);
	int getTeamId() const;
	void setTeamId(int teamId);
	virtual void kill();
	virtual bool isAlive() const;
	virtual Type getType() const;
	void setType(Type type);
	virtual bool checkCollisionsWithBombs(const irr::core::vector3df &pos,
				      const std::vector<AEntity *> &entities,
				      int tileSize);
	void calculMovements(
		const std::vector<std::pair<EventManager::Action, EventManager::InputType>> &events,
		irr::core::vector3df &oldPositions);
	void calculRotation(const irr::core::vector3df &oldPositions);
	void refreshB3DAnimation();
	virtual bool calculAnimations(const irr::core::vector3df &oldPositions);
	virtual void draw();
	void processActions(const std::vector<std::pair<EventManager::Action, EventManager::InputType >> &events, Map &map, std::vector<AEntity *> &entities);
	ResourceManager::Name getResName() const;
	void toggleAnimation(bool activated);
	virtual ~AEntity();
	virtual std::string serialize();
	virtual void deserialize(const std::vector<std::string> &stats);
	void hardKill();

protected:
	irr::scene::IAnimatedMesh *animatedMesh;
	irr::scene::IAnimatedMeshSceneNode *animatedMeshSceneNode;
	irr::core::vector3df pos;
	irr::f32 angle;
	irr::f32 speed;
	Status status;
	int teamId;
	bool alive;
	Type type;
	bool isMD2;
	std::map<Status, std::pair<irr::s32, irr::s32>> animationsTimeB3D;
	std::map<Status, irr::f32> animationsSpeedB3D;
	ResourceManager::Name resName;
	irr::f32 oldAnimationSpeed;
};

#endif //CPP_INDIE_STUDIO_AENTITY_HPP
