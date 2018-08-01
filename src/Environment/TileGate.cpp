/*
** EPITECH PROJECT, 2018
** TileGate
** File description:
** Implementation of TileGate
*/

#include <Window.hpp>
#include "TileGate.hpp"

TileGate::TileGate() : type(ITile::GATE), luaCharacter('G'), isOpen(false)
{

}

ITile::Type TileGate::getType() const
{
	return type;
}

void TileGate::draw(irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	this->x = x;
	this->x = y;
	this->tileSize = tileSize;

	const irr::scene::IGeometryCreator *g = Window::device->getSceneManager()->getGeometryCreator();
	irr::scene::IMesh *plane = g->createPlaneMesh(
		irr::core::dimension2d<irr::f32>((irr::f32)tileSize, (irr::f32)tileSize));
	ground = Window::device->getSceneManager()->addMeshSceneNode(plane);
	ground->setPosition(irr::core::vector3df((irr::f32)x * tileSize, 0, (irr::f32)y * tileSize));
	ground->setMaterialType(irr::video::EMT_SOLID);
	ground->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	ground->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::GATECLOSE).c_str()));
}

char TileGate::getLuaCharacter() const
{
	return luaCharacter;
}

TileGate::~TileGate()
{
	ground->remove();
}

void TileGate::open()
{
	isOpen = true;
	ground->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::GATEOPEN).c_str()));
}

bool TileGate::isIsOpen() const
{
	return isOpen;
}
