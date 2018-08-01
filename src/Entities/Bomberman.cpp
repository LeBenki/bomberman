/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Implementation of Player
*/

#include "JoystickManager.hpp"
#include "IndieExceptions.hpp"
#include "Bomberman.hpp"
#include "Window.hpp"
#include "AEntity.hpp"

#define HITBOX 10

Bomberman::Bomberman(irr::core::vector3df &pos, int teamId, Event::InputType input)
	: AEntity((ResourceManager::Name)teamId, pos, teamId, Type::BombermanType, false), monture(nullptr), zUp(20), inputType(input),
	maxBombs(1), range(1), canPassSoft(false),
	canKick(false), canThrow(false),
	currentBombs(0), curse(false), shield(false), redbomb(false), mount(false), skull(false), tookDoor(false), ps(nullptr)
{
	//Load bomb
	animatedMesh = Window::device->getSceneManager()->getMesh(ResourceManager::getRes(ResourceManager::MODEL, ResourceManager::BOMB).c_str());
	if (!animatedMesh)
		throw InitError("Bomb model preload error");
	Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::BOMB).c_str());
	Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::REDBOMB).c_str());

	animatedMeshSceneNode->setScale({17 , 17 , 17});
	auto tmp = getPosition();
	tmp.Y -= zUp;
	setPosition(tmp);
	setAnimationsData();
	refreshB3DAnimation();
	dieLastTime = std::chrono::high_resolution_clock::now();
	skullLastTime = std::chrono::high_resolution_clock::now();
}

void Bomberman::handleEvent(Map &map, std::vector<AEntity *> &entities)
{
	std::vector<std::pair<EventManager::Action, EventManager::InputType>> events;

	switch (inputType) {
		case Event::InputType::KEYBOARD:
			events = EventManager::getEvents();
			break;
		default:
			events = JoystickManager::getEvents(inputType - Event::CONTROLLER1);
			break;
	}
	doBombermanThings(events, map, entities);
}

void Bomberman::putDownBomb(const Map &map, std::vector<AEntity *> &entities)
{
	irr::core::vector3df i = (irr::core::vector3df &) getPosition();
	i.Z = i.Z - map.getTileSize() / 2;
	i.X = i.X + map.getTileSize() / 2;
	i.Z += (irr::u32)abs(i.Z) % map.getTileSize();
	i.X -= (irr::u32)abs(i.X) % map.getTileSize();
	int x = (int)(i.X / map.getTileSize());
	int y = (int)(i.Z / map.getTileSize() * -1);
	if (map.getTiles()[y][x]->getType() != ITile::EMPTY && map.getTiles()[y][x]->getType() != ITile::GATE)
		return;
	for (auto entity : entities) {
		if (entity->getType() == Type::BombType
		    && i.Z == entity->getPosition().Z
		    && i.X == entity->getPosition().X)
			return;
	}
	++currentBombs;
	if (monture)
		i.Y -= zUp;
	entities.push_back(new Bomb(i, teamId, range, &currentBombs, redbomb));
}

bool Bomberman::calculAnimations(const irr::core::vector3df &oldPositions)
{
	if (status == DABBING && animatedMeshSceneNode->getFrameNr() > 210) {
		status = IDLE;
		refreshB3DAnimation();
	}
	if (oldPositions == getPosition()) {
		if (status != IDLE && status != DABBING) {
			status = IDLE;
			refreshB3DAnimation();
		}
		return true;
	}
	else if (status != RUNNING && !mount) {
		status = RUNNING;
		refreshB3DAnimation();
	}
	return false;
}

Bomberman::~Bomberman()
{
	if (ps)
		ps->remove();
}

void Bomberman::move(const irr::core::vector3df &vec, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions)
{
	if (canKick)
		kickBombs(oldPositions, entities, map.getTileSize());
	if (checkCollisionsWithBombs(oldPositions, entities, map.getTileSize()))
		return;
	if (map.checkCollision(getPosition().X, getPosition().Z, vec.X, vec.Z, canPassSoft))
		return;
	if (map.checkFire(vec.X, vec.Z)) {
		kill();
		return;
	}
	if (checkCollisionsWithMobs(entities)) {
		kill();
		return;
	}
	if (map.checkDoor(vec.X, vec.Z)) {
		tookDoor = true;
		return;
	}
	if (skull)
		checkCollisionsWithBombermans(entities);
	map.checkBonus(*this, vec.X, vec.Z);
	setPosition(vec);
}

static inline bool checkCollisionsWithHitBox(irr::f32 a, irr::f32 b)
{
	return (abs(b - a) <= HITBOX);
}

bool Bomberman::checkCollisionsWithBombermans(std::vector<AEntity *> &entities)
{
	for (auto &entity : entities) {
		if (entity->getType() != AEntity::BombermanType || entity == this)
			continue;
		if (checkCollisionsWithHitBox(entity->getPosition().X,getPosition().X)
		    && checkCollisionsWithHitBox(entity->getPosition().Z, getPosition().Z)) {
			Bomberman *bomberman = (Bomberman *)entity;
			skullLastTime = std::chrono::high_resolution_clock::now();
			if (skull && !bomberman->isSkull()) {
				if (bomberman->setSkull())
					skull = false;
			}
		}
	}
	return false;
}

bool Bomberman::isSkull() const
{
	return skull;
}

bool Bomberman::checkCollisionsWithMobs(const std::vector<AEntity *> &entities)
{
	for (auto &entity : entities) {
		if (entity->getType() != AEntity::MOB)
			continue;
		if (checkCollisionsWithHitBox(entity->getPosition().X,getPosition().X)
		    && checkCollisionsWithHitBox(entity->getPosition().Z, getPosition().Z))
			return true;
	}
	return false;
}

void Bomberman::kickBombs(const irr::core::vector3df &pos,
			const std::vector<AEntity *> &entities,
			int tileSize)
{
	irr::f32 entityY = pos.Z - (irr::f32)tileSize / 2;
	irr::f32 entityX = pos.X + (irr::f32)tileSize / 2;
	entityY += (irr::f32)std::fmod(abs(entityY), tileSize);
	entityX -= (irr::f32)std::fmod(abs(entityX), tileSize);
	size_t playerX = (size_t) (entityX / tileSize);
	size_t playerY = (size_t) (entityY * -1 / tileSize);

	irr::f32 oldEntityY = getPosition().Z - (irr::f32)tileSize / 2;
	irr::f32 oldEntityX = getPosition().X + (irr::f32)tileSize / 2;
	oldEntityY += (irr::f32)std::fmod(abs(oldEntityY), tileSize);
	oldEntityX -= (irr::f32)std::fmod(abs(oldEntityX), tileSize);
	size_t oldPlayerX = (size_t) (oldEntityX / tileSize);
	size_t oldPlayerY = (size_t) (oldEntityY * -1 / tileSize);

	for (auto &entity : entities) {
		if (entity == this)
			continue;
		if (playerX == oldPlayerX && playerY == oldPlayerY)
			continue;
		if (entity->getType() != AEntity::BombType)
			continue;
		irr::f32 y = entity->getPosition().Z - tileSize / 2;
		irr::f32 x = entity->getPosition().X + tileSize / 2;
		y += (irr::f32)std::fmod(abs(y), tileSize);
		x -= (irr::f32)std::fmod(abs(x), tileSize);
		size_t x2 = (size_t) (x / tileSize);
		size_t y2 = (size_t) (y * -1 / tileSize);
		if (playerX == x2 && playerY == y2) {
			Bomb *bomb = (Bomb *)entity;
			bomb->setDirection(calculDirection(playerX, playerY, oldPlayerX, oldPlayerY));
			return;
		}
	}
}

Bomb::Direction Bomberman::calculDirection(size_t playerX, size_t playerY, size_t oldPlayerX, size_t oldPlayerY)
{
	if (playerX > oldPlayerX)
		return Bomb::RIGHT;
	if (playerX < oldPlayerX)
		return Bomb::LEFT;
	if (playerY > oldPlayerY)
		return Bomb::DOWN;
	if (playerY < oldPlayerY)
		return Bomb::UP;
	return Bomb::NONE;
}

void Bomberman::setAnimationsData()
{
	animationsSpeedB3D[IDLE] = 20;
	animationsSpeedB3D[DABBING] = 20;
	animationsSpeedB3D[RUNNING] = 120;

	animationsTimeB3D[IDLE] = {200, 300};
	animationsTimeB3D[DABBING] = {170, 220};
	animationsTimeB3D[RUNNING] = {0, 80};
}

void Bomberman::draw()
{
	AEntity::draw();
	animatedMeshSceneNode->setScale({15 , 15 , 15});
	setAnimationsData();
	refreshB3DAnimation();
	if (shield && Window::settings.isParticles())
		shieldFX();
}
void Bomberman::kill()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto aliveSince = std::chrono::duration_cast<std::chrono::milliseconds>
		(time - dieLastTime).count();

	if (aliveSince >= 600)
	{
		if (mount) {
			SoundEngine::playSound("Death");
			monture->kill();
			status = IDLE;
			mount = false;
			monture = nullptr;
			auto tmp = getPosition();
			tmp.Y -= zUp;
			setPosition(tmp);
		}
		else if (shield) {
			shield = false;
			if (ps) {
				ps->remove();
				ps = nullptr;
			}
		}
		else
			AEntity::kill();
		dieLastTime = std::chrono::high_resolution_clock::now();
	}
}

void Bomberman::shieldFX()
{
	ps = Window::device->getSceneManager()->addParticleSystemSceneNode(false);
	irr::scene::IParticleEmitter *em = ps->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(-2, 0, -2, 2, 1, 2),
		irr::core::vector3df(0.0f, 0.005f, 0.0f),
		80, 100,
		irr::video::SColor(0, 255, 255, 255),
		irr::video::SColor(0, 255, 255, 255),
		200, 400,
		0,
		irr::core::dimension2df(0.f, 0.f),
		irr::core::dimension2df(30.f, 30.f));
	ps->setEmitter(em);
	em->drop();
	irr::scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();
	ps->addAffector(paf);
	paf->drop();
	irr::core::vector3df pos = getPosition();
	pos.Y += 15;
	ps->setPosition(pos);
	ps->setScale(irr::core::vector3df(1, 1, 1));
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::PARTICLES_SHIELD).c_str()));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void Bomberman::rangeUp()
{
	if (range < 5)
		++range;
}

void Bomberman::bombsUp()
{
	if (maxBombs < 5)
		++maxBombs;
}

void Bomberman::passSoft()
{
	canPassSoft = true;
}

void Bomberman::setCanKick()
{
	canKick = true;
}

void Bomberman::setShield()
{
	if (!shield && Window::settings.isParticles())
		shieldFX();
	shield = true;
}

void Bomberman::setRedbomb()
{
	redbomb = true;
}

void Bomberman::setMount()
{
	mount = true;
}

void Bomberman::speedUp()
{
	if (speed < 1.5)
		speed += (irr::f32)0.1;
}

void Bomberman::doBombermanThings(std::vector<std::pair<EventManager::Action, EventManager::InputType >> events, Map &map, std::vector<AEntity *> &entities)
{
	if (skull)
		processSkull(events);
	processActions(events, map, entities);
	if (mount) {
		if (!monture) {
			auto pos = getPosition();
			monture = new Mount(pos, teamId);
			entities.push_back(monture);
			auto tmp = getPosition();
			tmp.Y += zUp;
			monture->setPosition(tmp);
			setPosition(tmp);
		}
		monture->processActions(events, map, entities);
	}
	for (auto &i : events) {
		if (i.first == EventManager::ATTACK && i.second == EventManager::RELEASED
		    && currentBombs < maxBombs)
			putDownBomb(map, entities);
		else if (i.first == EventManager::DAB && i.second == EventManager::RELEASED
			&& monture)
			SoundEngine::playSound("Mlem");
	}

}

std::string Bomberman::serialize()
{
	// maxBombs;range;canPassSoft;canKick;canThrow;currentBombs;curse;shield;redbomb;mount
	return std::to_string(maxBombs)+ ";" +
	       std::to_string(range) + ";" +
	       (canPassSoft ? "True" : "False") + ";" +
	       (canKick ? "True" : "False") + ";" +
	       (canThrow ? "True" : "False") + ";" +
	       (curse ? "True" : "False") + ";" +
	       (shield ? "True" : "False") + ";" +
	       (redbomb ? "True" : "False") + ";" +
	       (mount ? "True" : "False") + ";" +
	       (skull ? "True" : "False") + ';' +
	       std::to_string(inputType);
}

void Bomberman::deserialize(const std::vector<std::string> &stats)
{
	maxBombs = stoi(stats.at(2));
	range = stoi(stats.at(3));
	canPassSoft = stats.at(4) == "True";
	canKick = stats.at(5) == "True";
	canThrow = stats.at(6) == "True";
	currentBombs = 0;
	curse = stats.at(7) == "True";
	shield = stats.at(8) == "True";
	redbomb = stats.at(9) == "True";
	mount = stats.at(10) == "True";
	skull = stats.at(11) == "True";
}

int Bomberman::getMaxBombs() const
{
	return maxBombs;
}

int Bomberman::getRange() const
{
	return range;
}

bool Bomberman::isCanPassSoft() const
{
	return canPassSoft;
}

bool Bomberman::isCanKick() const
{
	return canKick;
}

int Bomberman::getCurrentBombs() const
{
	return currentBombs;
}

bool Bomberman::isShield() const
{
	return shield;
}

bool Bomberman::isRedbomb() const
{
	return redbomb;
}

bool Bomberman::isMount() const
{
	return mount;
}

void Bomberman::rangeMax()
{
	range = 5;
}

bool Bomberman::setSkull()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto aliveSince = std::chrono::duration_cast<std::chrono::milliseconds>
		(time - skullLastTime).count();

	if (aliveSince >= 1000)
	{
		skullLastTime = std::chrono::high_resolution_clock::now();
		skull = true;
		return true;
	}
	return false;
}

void Bomberman::processSkull(
	std::vector<std::pair<EventManager::Action, EventManager::InputType>> &events)
{
	for (auto &event : events) {
		if (event.first == EventManager::MOVE_UP)
			event.first = EventManager::MOVE_DOWN;
		else if (event.first == EventManager::MOVE_DOWN)
			event.first = EventManager::MOVE_UP;
		else if (event.first == EventManager::MOVE_LEFT)
			event.first = EventManager::MOVE_RIGHT;
		else if (event.first == EventManager::MOVE_RIGHT)
			event.first = EventManager::MOVE_LEFT;
	}
}

bool Bomberman::isTookDoor() const
{
	return tookDoor;
}

void Bomberman::setTookDoor(bool tookDoor)
{
	Bomberman::tookDoor = tookDoor;
}

void Bomberman::dab()
{
	status = DABBING;
	animatedMeshSceneNode->setFrameLoop(animationsTimeB3D[status].first, 200);
	animatedMeshSceneNode->setAnimationSpeed(animationsSpeedB3D[status]);
}
void Bomberman::setPosition(const irr::core::vector3df &vec)
{
	AEntity::setPosition(vec);
	if (monture)
		monture->setPosition(vec);
	if (ps && Window::settings.isParticles()) {
		irr::core::vector3df pos(vec.X, vec.Y + 15, vec.Z);
		ps->setPosition(pos);
	}
}
