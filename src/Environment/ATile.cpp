/*
** EPITECH PROJECT, 2018
** ATile
** File description:
** Implementation of ATile
*/

#include <BiomeManager.hpp>
#include <Window.hpp>
#include "ATile.hpp"

ATile::ATile(BiomeManager::Name biome, Type type, char luaCharacter)
	: type(type), luaCharacter(luaCharacter), biome(biome)
{

}

ATile::~ATile()
{
	ground->remove();
}

ITile::Type ATile::getType() const
{
	return type;
}

void ATile::draw(irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	const irr::scene::IGeometryCreator *g = Window::device->getSceneManager()->getGeometryCreator();
	irr::scene::IMesh *plane = g->createPlaneMesh(
		irr::core::dimension2d<irr::f32>((irr::f32)tileSize, (irr::f32)tileSize));
	ground = Window::device->getSceneManager()->addMeshSceneNode(plane);
	ground->setPosition(irr::core::vector3df((irr::f32)x * tileSize, 0, (irr::f32)y * tileSize));
	ground->setMaterialType(irr::video::EMT_SOLID);
	ground->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	ground->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(BiomeManager::getPathFromNameAndType(biome, BiomeManager::FloorTexture).c_str()));
}

char ATile::getLuaCharacter() const
{
	return luaCharacter;
}
