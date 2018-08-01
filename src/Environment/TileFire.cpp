/*
** EPITECH PROJECT, 2018
** TileFire
** File description:
** Implementation of TileFire
*/

#include "Window.hpp"
#include "TileFire.hpp"

TileFire::TileFire(BiomeManager::Name biome, double x, double y, bool wasSoft, ITile::Type type)
	: ATile(biome, type, 'F'), _wasSoft(wasSoft), lightX(x), lightY(y)
{
}

TileFire::~TileFire()
{
	if (!Window::settings.isParticles())
		wall->remove();
	else
		ps->remove();
	light->remove();
}

bool TileFire::isFinish() const
{
	std::chrono::time_point<std::chrono::high_resolution_clock> new_tick =
		std::chrono::high_resolution_clock::now();

	auto aliveSince = std::chrono::duration_cast<std::chrono::milliseconds>
		(new_tick - _t).count();
	return aliveSince >= 500;
}

void TileFire::draw(irr::s32 x, irr::s32 y,
		    irr::s32 tileSize)
{
	ATile::draw(x, y, tileSize);

	_t = std::chrono::high_resolution_clock::now();
	if (!Window::settings.isParticles())
	{
		irr::scene::IAnimatedMesh *cube = Window::device->getSceneManager()->getMesh(
			ResourceManager::getRes(ResourceManager::MODEL,
						ResourceManager::FIRE).c_str());
		wall = Window::device->getSceneManager()->addAnimatedMeshSceneNode(
			cube);
		wall->setScale(irr::core::vector3df((irr::f32) tileSize,
						    (irr::f32) tileSize,
						    (irr::f32) tileSize));
		wall->setPosition(
			irr::core::vector3df((irr::f32) x * tileSize, 0,
					     (irr::f32) y * tileSize));
		wall->setMaterialType(
			irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		wall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		wall->setMaterialTexture(0,
					 Window::device->getVideoDriver()->getTexture(
						 ResourceManager::getRes(
							 ResourceManager::TEXTURE,
							 ResourceManager::FIRE).c_str()));
		wall->render();
	}
	else
	{
		ps = Window::device->getSceneManager()->addParticleSystemSceneNode(false);

		irr::scene::IParticleEmitter *em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-7, 0, -7, 7, 1, 7),
			irr::core::vector3df(0.0f, 0.03f, 0.0f),
			80, 100,
			irr::video::SColor(0, 0, 0, 0),
			irr::video::SColor(0, 255, 255, 255),
			800, 2000,
			0,
			irr::core::dimension2df(20.f, 20.f),
			irr::core::dimension2df(30.f, 30.f));
		ps->setEmitter(em);
		em->drop();
		irr::scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();
		ps->addAffector(paf);
		paf->drop();
		ps->setPosition(irr::core::vector3df((irr::f32) x * tileSize, 0, (irr::f32) y * tileSize));
		ps->setScale(irr::core::vector3df(1, 1, 1));
		ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, Window::device->getVideoDriver()->getTexture(ResourceManager::getRes(ResourceManager::TEXTURE, ResourceManager::PARTICLES_FIRE).c_str()));
		ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	}
	light = Window::device->getSceneManager()->addLightSceneNode(
		nullptr, irr::core::vector3df((irr::f32) lightX,
					      (irr::f32)tileSize / 2,
					      (irr::f32) lightY),
		irr::video::SColorf(0.8f, 0.8f, 0.2f, 0.2f), 20.0f);
	light->enableCastShadow(false);
}

bool TileFire::isSoft() const
{
	return _wasSoft;
}
