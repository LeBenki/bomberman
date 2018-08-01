/*
** EPITECH PROJECT, 2018
** ABonusTile
** File description:
** Implementation of ABonusTile
*/

#include <string>
#include <Window.hpp>
#include "ABonusTile.hpp"

ABonusTile::ABonusTile(ResourceManager::Name resName, BiomeManager::Name biome, Type type, char luaCharacter)
	: ATile(biome, type, luaCharacter), resName(resName)
{
	rotY = 0;
}

ABonusTile::~ABonusTile()
{
	wall->remove();
}

void ABonusTile::draw(irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	ATile::draw(x, y, tileSize);
	irr::scene::IAnimatedMesh *cube = Window::device->getSceneManager()->getMesh(ResourceManager::getRes(ResourceManager::MODEL, resName).c_str());
	wall = Window::device->getSceneManager()->addAnimatedMeshSceneNode(cube);
	wall->setScale(irr::core::vector3df((irr::f32)tileSize, (irr::f32)tileSize, (irr::f32)tileSize));
	wall->setPosition(irr::core::vector3df((irr::f32)x * tileSize, (irr::f32)(tileSize / 2), (irr::f32)y * tileSize));
	wall->setMaterialType(irr::video::EMT_SOLID);
	wall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	wall->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, resName).c_str()));
	wall->render();
}

void ABonusTile::refresh()
{
	++rotY;
	if (rotY > 360)
		rotY = 0;
	wall->setRotation(irr::core::vector3df(0, rotY ,0));
}
