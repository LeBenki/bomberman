/*
** EPITECH PROJECT, 2018
** FallingBloc
** File description:
** Implementation of FallingBloc
*/

#include <Window.hpp>
#include "FallingBlock.hpp"

FallingBlock::FallingBlock(BiomeManager::Name resName, irr::core::vector3df &pos,
			   int tileSize, size_t destructionX, size_t destructionY)
	: tileSize(tileSize), destructedX(destructionX), destructedY(destructionY), name(resName), isDown(false)
{
	animatedMesh = Window::device->getSceneManager()->getMesh(BiomeManager::getPathFromNameAndType(resName, BiomeManager::HardWallModel).c_str());
	if (!animatedMesh)
		throw InitError("AEntity animatedMesh is null");
	animatedMeshSceneNode = Window::device->getSceneManager()->addAnimatedMeshSceneNode(animatedMesh);
	if (!animatedMeshSceneNode)
		throw InitError("AEntity animatedMeshSceneNode is null");
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	animatedMeshSceneNode->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(BiomeManager::getPathFromNameAndType(resName, BiomeManager::HardWallTexture).c_str()));
	animatedMeshSceneNode->setPosition(pos);
	animatedMeshSceneNode->setScale({(float)tileSize, (float)tileSize, (float)tileSize});
}

void FallingBlock::down(Map &map, std::vector<AEntity *> &entities)
{
	auto pos = animatedMeshSceneNode->getPosition();
	pos.Y -= 1;
	animatedMeshSceneNode->setPosition(pos);
	if (pos.Y < 0) {
		createBlock(map, entities);
		isDown = true;
	}
}

void FallingBlock::createBlock(Map &map, std::vector<AEntity *> &entities)
{
	auto ptr = map.getTiles()[destructedY][destructedX].release();
	delete ptr;
	map.getTiles()[destructedY][destructedX] = std::make_unique<TileHardWall>(name);
	map.getTiles()[destructedY][destructedX]->draw(
		static_cast<irr::s32>(destructedX),
		static_cast<irr::s32>(destructedY * -1), tileSize);

	for (auto &entity : entities)
	{
		irr::f32 y = entity->getPosition().Z - tileSize / 2;
		irr::f32 x = entity->getPosition().X + tileSize / 2;
		y += (irr::f32) std::fmod(abs(y), tileSize);
		x -= (irr::f32) std::fmod(abs(x), tileSize);
		size_t x2 = (size_t) (x / tileSize);
		size_t y2 = (size_t) (y * -1 / tileSize);
		if (x2 == destructedX && y2 == destructedY)
			entity->hardKill();
	}
}

FallingBlock::~FallingBlock()
{
	animatedMeshSceneNode->remove();
}

bool FallingBlock::isIsDown() const
{
	return isDown;
}
