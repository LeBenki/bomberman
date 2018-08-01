/*
** EPITECH PROJECT, 2018
** AnimatedTile
** File description:
** Implementation of AnimatedTile
*/

#include <Window.hpp>
#include "ABiomeTile.hpp"

ABiomeTile::ABiomeTile(BiomeManager::Name biome, Type type, char luaCharacter)
	: ATile(biome, type, luaCharacter)
{

}

void ABiomeTile::draw(irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	ATile::draw(x, y, tileSize);
	irr::scene::IAnimatedMesh *cube;
	if (type == HARD_WALL)
		cube = Window::device->getSceneManager()->getMesh(
			BiomeManager::getPathFromNameAndType(biome, BiomeManager::HardWallModel).c_str());
	else
		cube = Window::device->getSceneManager()->getMesh(
			BiomeManager::getPathFromNameAndType(biome, BiomeManager::SoftWallModel).c_str());
	wall = Window::device->getSceneManager()->addAnimatedMeshSceneNode(cube);
	wall->addShadowVolumeSceneNode();
	wall->setScale(irr::core::vector3df((irr::f32)tileSize, (irr::f32)tileSize, (irr::f32)tileSize));
	wall->setPosition(irr::core::vector3df((irr::f32)x * tileSize, 0, (irr::f32)y * tileSize));
	wall->setMaterialType(irr::video::EMT_SOLID);
	wall->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	if (type == HARD_WALL)
		wall->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(
			BiomeManager::getPathFromNameAndType(biome, BiomeManager::HardWallTexture).c_str()));
	else
		wall->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(
			BiomeManager::getPathFromNameAndType(biome, BiomeManager::SoftWallTexture).c_str()));
}

ABiomeTile::~ABiomeTile()
{
	wall->remove();
}
