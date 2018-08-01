/*
** EPITECH PROJECT, 2018
** Bomb
** File description:
** Implementation of Bomb
*/

#include <Window.hpp>
#include "Bomb.hpp"

Bomb::Bomb(irr::core::vector3df &pos, int teamId, int range, int *currentBombFromBomberman, bool isRed)
	: AEntity(isRed ? ResourceManager::REDBOMB : ResourceManager::BOMB, pos, teamId, Type::BombType),
	  currentBombFromBomberman(currentBombFromBomberman), range(range), exploded(false), isRed(isRed), explosionSound(true), moving(false), direction(NONE), ps(nullptr)
{
	_t = std::chrono::high_resolution_clock::now();
	animatedMeshSceneNode->setScale({15, 15, 15});
	animatedMeshSceneNode->setAnimationSpeed(100);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	if (Window::settings.isParticles()) {
		ps = Window::device->getSceneManager()->addParticleSystemSceneNode(false);

		irr::scene::IParticleEmitter *em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-2, 0, -2, 2, 1, 2),
			irr::core::vector3df(0.0f, 0.01f, 0.0f),
			80, 100,
			irr::video::SColor(0, 255, 255, 255),
			irr::video::SColor(0, 255, 255, 255),
			800, 2000,
			0,
			irr::core::dimension2df(2.f, 2.f),
			irr::core::dimension2df(3.f, 3.f));
		ps->setEmitter(em);
		em->drop();
		irr::scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();
		ps->addAffector(paf);
		paf->drop();
		auto position = pos;
		position.Y += 15;
		ps->setPosition(irr::core::vector3df(position));
		ps->setScale(irr::core::vector3df(1, 1, 1));
		ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::PARTICLES_SMOKE).c_str()));
		ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	}
}

void Bomb::handleEvent(Map &map, std::vector<AEntity *> &entities)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> new_tick =
		std::chrono::high_resolution_clock::now();

	if (direction == NONE)
	{
		auto aliveSince = std::chrono::duration_cast<std::chrono::milliseconds>
			(new_tick - _t).count();
		if (aliveSince >= 1500 && alive && !exploded && explosionSound) {
			SoundEngine::playSound("Bomb");
			explosionSound = false;
		}
		else if (aliveSince >= 2000 && alive && !exploded)
			explode(map, entities);
	}
	else
	{
		_t = std::chrono::high_resolution_clock::now();
		calculMovements(map, entities);
	}
}

void Bomb::explode(Map &map, std::vector<AEntity *> &entities)
{
	auto x = (size_t)(getPosition().X / map.getTileSize() + 0.5);
	auto y = (size_t)(getPosition().Z * -1 / map.getTileSize() + 0.5);

	exploded = true;
	*currentBombFromBomberman -= 1;
	map.breakSoftWallAndBonus(x, y);
	map.fireOnEmpty(x, y);
	explodeEntities(map, entities, map.getTileSize(), x, y);
	for (int i = 1; i <= range && (x + i) < map.getNbOfHorizontalTiles() ; ++i)
	{
		if (map.getTiles()[y][x + i]->getType() == ITile::HARD_WALL)
			break;
		if (map.getTiles()[y][x + i]->getType() == ITile::SOFT_WALL ||
			map.getTiles()[y][x + i]->getType() == ITile::BONUS) {
			map.breakSoftWallAndBonus(x + i, y);
			if (!isRed)
				break;
		}
		map.fireOnEmpty(x + i, y);
		explodeEntities(map, entities, map.getTileSize(), x + i, y);
	}
	for (int i = 1; i <= range && (x - i) > 0 ; ++i)
	{
		if (map.getTiles()[y][x - i]->getType() == ITile::HARD_WALL)
			break;
		if (map.getTiles()[y][x - i]->getType() == ITile::SOFT_WALL ||
			map.getTiles()[y][x - i]->getType() == ITile::BONUS) {
			map.breakSoftWallAndBonus(x - i, y);
			if (!isRed)
				break;
		}
		map.fireOnEmpty(x - i, y);
		explodeEntities(map, entities, map.getTileSize(), x - i, y);
	}
	for (int i = 1; i <= range && (y + i) < map.getNbOfVerticalTiles() ; ++i)
	{
		if (map.getTiles()[y + i][x]->getType() == ITile::HARD_WALL)
			break;
		if (map.getTiles()[y + i][x]->getType() == ITile::SOFT_WALL ||
			map.getTiles()[y + i][x]->getType() == ITile::BONUS) {
			map.breakSoftWallAndBonus(x, y + i);
			if (!isRed)
				break;
		}
		map.fireOnEmpty(x, y + i);
		explodeEntities(map, entities, map.getTileSize(), x, y + i);
	}
	for (int i = 1; i <= range && (y - i) > 0 ; ++i)
	{
		if (map.getTiles()[y - i][x]->getType() == ITile::HARD_WALL)
			break;
		if (map.getTiles()[y - i][x]->getType() == ITile::SOFT_WALL ||
			map.getTiles()[y - i ][x]->getType() == ITile::BONUS) {
			map.breakSoftWallAndBonus(x, y - i);
			if (!isRed)
				break;
		}
		map.fireOnEmpty(x, y - i);
		explodeEntities(map, entities, map.getTileSize(), x, y - i);
	}
	kill();
}

void Bomb::explodeEntities(Map &map, std::vector<AEntity *> &entities, int tileSize, size_t xBomb, size_t yBomb)
{
	for (auto entity : entities)
	{
		irr::f32 y = entity->getPosition().Z - (irr::f32)tileSize / 2;
		irr::f32 x = entity->getPosition().X + (irr::f32)tileSize / 2;
		y += (irr::f32)std::fmod(abs(y), tileSize);
		x -= (irr::f32)std::fmod(abs(x), tileSize);
		auto x2 = (irr::s32) (x / tileSize);
		auto y2 = (irr::s32) (y * -1 / tileSize);
		if (x2 == (irr::s32)xBomb && y2 == (irr::s32)yBomb) {
			if (entity->getType() != Type::BombType) {
				entity->kill();
			}
			else if (entity->getType() == BombType && this != entity) {
				Bomb *bomb = (Bomb *)(entity);
				if (!bomb->isExploded())
					bomb->explode(map, entities);
			}
		}
	}
}

Bomb::~Bomb()
{
	if (ps)
		ps->remove();
}

bool Bomb::isMoving() const
{
	return moving;
}

void Bomb::move(const irr::core::vector3df &vec, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions)
{
	if (checkCollisionsWithBombs(oldPositions, entities, map.getTileSize()))
	{
		direction = NONE;
		moving = false;
		return;
	}
	if (map.checkCollision(getPosition().X, getPosition().Z, vec.X, vec.Z, false, true, direction))
	{
		direction = NONE;
		moving = false;
		return;
	}
	moving = true;
	setPosition(vec);
	if (ps)
		ps->setPosition(vec);
}

bool Bomb::isExploded() const
{
	return exploded;
}

const irr::core::vector3df &Bomb::getPosition() const
{
	return AEntity::getPosition();
}

bool Bomb::isAlive() const
{
	return AEntity::isAlive();
}

AEntity::Type Bomb::getType() const
{
	return AEntity::getType();
}

void Bomb::setDirection(Direction direction1)
{
	direction = direction1;
}

void Bomb::calculMovements(Map &map, std::vector<AEntity *> &entities)
{
	processActions(fillEventVector(), map, entities);
}

std::vector<std::pair<EventManager::Action, EventManager::InputType >> Bomb::fillEventVector()
{
	EventManager::Action action{};
	std::vector<std::pair<EventManager::Action, EventManager::InputType >> eventVector;

	switch (direction) {
		case UP:
			action = EventManager::MOVE_UP;
			break;
		case RIGHT:
			action = EventManager::MOVE_RIGHT;
			break;
		case DOWN:
			action = EventManager::MOVE_DOWN;
			break;
		case LEFT:
			action = EventManager::MOVE_LEFT;
			break;
		default:
			break;
	}
	eventVector.emplace_back(action, EventManager::PRESSED);
	return eventVector;
}
bool Bomb::checkCollisionsWithBombs(const irr::core::vector3df &pos,
				    const std::vector<AEntity *> &entities,
				    int tileSize)
{
	irr::core::vector3df tmp = pos;

	switch (direction) {
		case UP:
			tmp.Z += tileSize / 2;
			break;
		case DOWN:
			tmp.Z -= tileSize / 2;
			break;
		case RIGHT:
			tmp.X += tileSize / 2;
			break;
		case LEFT:
			tmp.X -= tileSize / 2;
			break;
		default:
			break;
	}

	irr::f32 entityY = tmp.Z - (irr::f32) tileSize / 2;
	irr::f32 entityX = tmp.X + (irr::f32) tileSize / 2;
	entityY += (irr::f32) std::fmod(abs(entityY), tileSize);
	entityX -= (irr::f32) std::fmod(abs(entityX), tileSize);

	size_t entityX2 = (size_t) (entityX / tileSize);
	size_t entityY2 = (size_t) (entityY * -1 / tileSize);

	irr::f32 oldEntityY = getPosition().Z - (irr::f32) tileSize / 2;
	irr::f32 oldEntityX = getPosition().X + (irr::f32) tileSize / 2;
	oldEntityY += (irr::f32) std::fmod(abs(oldEntityY), tileSize);
	oldEntityX -= (irr::f32) std::fmod(abs(oldEntityX), tileSize);
	size_t oldEntityX2 = (size_t) (oldEntityX / tileSize);
	size_t oldEntityY2 = (size_t) (oldEntityY * -1 / tileSize);

	for (auto &entity : entities)
	{
		if (entity == this)
			continue;
		if (entityX2 == oldEntityX2 && entityY2 == oldEntityY2)
			continue;
		if (entity->getType() != AEntity::BombType)
			continue;
		irr::f32 y = entity->getPosition().Z - tileSize / 2;
		irr::f32 x = entity->getPosition().X + tileSize / 2;
		y += (irr::f32) std::fmod(abs(y), tileSize);
		x -= (irr::f32) std::fmod(abs(x), tileSize);
		size_t x2 = (size_t) (x / tileSize);
		size_t y2 = (size_t) (y * -1 / tileSize);
		if (entityX2 == x2 && entityY2 == y2)
			return true;
	}
	return false;
}

void Bomb::draw()
{
	AEntity::draw();
	animatedMeshSceneNode->setScale({15, 15, 15});
	animatedMeshSceneNode->setAnimationSpeed(100);
	if (Window::settings.isParticles()) {
		ps = Window::device->getSceneManager()->addParticleSystemSceneNode(false);

		irr::scene::IParticleEmitter *em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-2, 0, -2, 2, 1, 2),
			irr::core::vector3df(0.0f, 0.01f, 0.0f),
			80, 100,
			irr::video::SColor(0, 255, 255, 255),
			irr::video::SColor(0, 255, 255, 255),
			800, 2000,
			0,
			irr::core::dimension2df(2.f, 2.f),
			irr::core::dimension2df(3.f, 3.f));
		ps->setEmitter(em);
		em->drop();
		irr::scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();
		ps->addAffector(paf);
		paf->drop();
		auto position = pos;
		position.Y += 15;
		ps->setPosition(irr::core::vector3df(position));
		ps->setScale(irr::core::vector3df(1, 1, 1));
		ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::PARTICLES_SMOKE).c_str()));
		ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	}
}

const std::chrono::time_point<std::chrono::high_resolution_clock> &
Bomb::getTime() const
{
	return _t;
}

void Bomb::setTime(
	const std::chrono::time_point<std::chrono::high_resolution_clock> &_t)
{
	Bomb::_t = _t;
}
