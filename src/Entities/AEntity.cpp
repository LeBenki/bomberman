/*
** EPITECH PROJECT, 2018
** AEntity
** File description:
** Implementation of AEntity
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include "IndieExceptions.hpp"
#include "Window.hpp"
#include "AEntity.hpp"

AEntity::AEntity(ResourceManager::Name resName,
		 irr::core::vector3df &pos, int teamId, Type type, bool isMD2)
	: angle(0), speed(1), status(IDLE),
	  teamId(teamId), alive(true), type(type), isMD2(isMD2), resName(resName), oldAnimationSpeed((irr::f32)0)
{
	animatedMesh = Window::device->getSceneManager()->getMesh(ResourceManager::getRes(ResourceManager::MODEL, resName).c_str());
	if (!animatedMesh)
		throw InitError("AEntity animatedMesh is null");
	animatedMeshSceneNode = Window::device->getSceneManager()->addAnimatedMeshSceneNode(animatedMesh);
	if (!animatedMeshSceneNode)
		throw InitError("AEntity animatedMeshSceneNode is null");
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	if (isMD2)
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
	animatedMeshSceneNode->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, resName).c_str()));
	setPosition(pos);
}

AEntity::~AEntity()
{
	animatedMeshSceneNode->remove();
}

const irr::core::vector3df &AEntity::getPosition() const
{
	return animatedMeshSceneNode->getPosition();
}

void AEntity::setPosition(const irr::core::vector3df &pos)
{
	animatedMeshSceneNode->setPosition(pos);
	this->pos = irr::core::vector3df(pos.X, pos.Y, pos.Z);
}

double AEntity::getSpeed() const
{
	return speed;
}

void AEntity::setSpeed(irr::f32 speed)
{
	AEntity::speed = speed;
}

void AEntity::move(const irr::core::vector3df &vec, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions)
{
	if (checkCollisionsWithBombs(oldPositions, entities, map.getTileSize()))
		return;
	if (map.checkCollision(getPosition().X, getPosition().Z, vec.X, vec.Z, false))
		return;
	if (map.checkFire(vec.X, vec.Z)) {
		kill();
		return;
	}
	setPosition(vec);
}

int AEntity::getTeamId() const
{
	return teamId;
}

void AEntity::setTeamId(int teamId)
{
	this->teamId = teamId;
}

void AEntity::calculMovements(const std::vector<std::pair<EventManager::Action, EventManager::InputType >> &events, irr::core::vector3df &oldPositions)
{
	for (std::pair<EventManager::Action, EventManager::InputType> event : events)
	{
		if (event.second != EventManager::PRESSED)
			continue;
		switch (event.first)
		{
			case EventManager::MOVE_UP:
				oldPositions.Z += speed;
				break;
			case EventManager::MOVE_DOWN:
				oldPositions.Z -= speed;
				break;
			case EventManager::MOVE_RIGHT:
				oldPositions.X += speed;
				break;
			case EventManager::MOVE_LEFT:
				oldPositions.X -= speed;
				break;
			case EventManager::DAB:
				if (!isMD2) {
					status = DABBING;
					refreshB3DAnimation();
				}
				break;
			default:
				break;
		}
	}
}

void AEntity::calculRotation(const irr::core::vector3df &oldPositions)
{
	angle = (irr::f32)(atan2(getPosition().Z - oldPositions.Z,
				 oldPositions.X - getPosition().X) * 180 / M_PI);
	if (isMD2)
		animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle, 0));
	else
		animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle - 90 % 360, 0));
}

bool AEntity::calculAnimations(const irr::core::vector3df &oldPositions)
{
	if (!isMD2 && status == DABBING && animatedMeshSceneNode->getFrameNr() > 210) {
		status = IDLE;
		refreshB3DAnimation();
	}
	if (oldPositions == getPosition()) {
		if (status != IDLE && ((status != DABBING) || isMD2)) {
			status = IDLE;
			if (isMD2)
				animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
			else
				refreshB3DAnimation();
		}
		return true;
	}
	else if (status != RUNNING) {
		status = RUNNING;
		if (isMD2)
			animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_RUN);
		else
			refreshB3DAnimation();
	}
	return false;
}

void AEntity::processActions(
	const std::vector<std::pair<EventManager::Action, EventManager::InputType >> &events, Map &map, std::vector<AEntity *> &entities)
{
	irr::core::vector3df oldPositions = getPosition();

	calculMovements(events, oldPositions);
	if (calculAnimations(oldPositions))
		return;
	calculRotation(oldPositions);
	move(oldPositions, map, entities, oldPositions);
}

void AEntity::kill()
{
	alive = false;
}

bool AEntity::isAlive() const
{
	return alive;
}

AEntity::Type AEntity::getType() const
{
	return type;
}

void AEntity::setType(AEntity::Type type)
{
	this->type = type;
}

bool AEntity::checkCollisionsWithBombs(const irr::core::vector3df &pos,
				       const std::vector<AEntity *> &entities,
				       int tileSize)
{
	irr::f32 entityY = pos.Z - (irr::f32)tileSize / 2;
	irr::f32 entityX = pos.X + (irr::f32)tileSize / 2;
	entityY += (irr::f32)std::fmod(abs(entityY), tileSize);
	entityX -= (irr::f32)std::fmod(abs(entityX), tileSize);
	size_t entityX2 = (size_t) (entityX / tileSize);
	size_t entityY2 = (size_t) (entityY * -1 / tileSize);

	irr::f32 oldEntityY = getPosition().Z - (irr::f32)tileSize / 2;
	irr::f32 oldEntityX = getPosition().X + (irr::f32)tileSize / 2;
	oldEntityY += (irr::f32)std::fmod(abs(oldEntityY), tileSize);
	oldEntityX -= (irr::f32)std::fmod(abs(oldEntityX), tileSize);
	size_t oldEntityX2 = (size_t) (oldEntityX / tileSize);
	size_t oldEntityY2 = (size_t) (oldEntityY * -1 / tileSize);

	for (auto &entity : entities) {
		if (entity == this)
			continue;
		if (entityX2 == oldEntityX2 && entityY2 == oldEntityY2)
			continue;
		if (entity->getType() != AEntity::BombType)
			continue;
		irr::f32 y = entity->getPosition().Z - tileSize / 2;
		irr::f32 x = entity->getPosition().X + tileSize / 2;
		y += (irr::f32)std::fmod(abs(y), tileSize);
		x -= (irr::f32)std::fmod(abs(x), tileSize);
		size_t x2 = (size_t) (x / tileSize);
		size_t y2 = (size_t) (y * -1 / tileSize);
		if (entityX2 == x2 && entityY2 == y2)
			return true;
	}
	return false;
}

void AEntity::refreshB3DAnimation()
{
	animatedMeshSceneNode->setFrameLoop(animationsTimeB3D[status].first, animationsTimeB3D[status].second);
	animatedMeshSceneNode->setAnimationSpeed(animationsSpeedB3D[status]);
}

void AEntity::setAnimationsData()
{
}

ResourceManager::Name AEntity::getResName() const
{
	return resName;
}

void AEntity::draw()
{
	animatedMesh = Window::device->getSceneManager()->getMesh(ResourceManager::getRes(ResourceManager::MODEL, resName).c_str());
	if (!animatedMesh)
		throw InitError("AEntity animatedMesh is null");
	animatedMeshSceneNode = Window::device->getSceneManager()->addAnimatedMeshSceneNode(animatedMesh);
	if (!animatedMeshSceneNode)
		throw InitError("AEntity animatedMeshSceneNode is null");
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	if (isMD2)
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
	animatedMeshSceneNode->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, resName).c_str()));
	animatedMeshSceneNode->setPosition(pos);
	if (isMD2)
		animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle, 0));
	else
		animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle - 90 % 360, 0));
}

std::string AEntity::serialize()
{
    return "NULL";
}

void AEntity::deserialize(const std::vector<std::string> &stats)
{
    (void)stats;
}

void AEntity::toggleAnimation(bool activated)
{
	irr::f32 speed = animatedMeshSceneNode->getAnimationSpeed();

	if (!activated) {
		oldAnimationSpeed = speed ? speed : oldAnimationSpeed;
		animatedMeshSceneNode->setAnimationSpeed((irr::f32) 0);
	}
	else
		animatedMeshSceneNode->setAnimationSpeed(speed ? speed : oldAnimationSpeed);
}

void AEntity::hardKill()
{
	alive = false;
}
