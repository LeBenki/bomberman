/*
** EPITECH PROJECT, 2018
** TileFire
** File description:
** Declaration of TileFire
*/

#ifndef INDIE_STUDIO_TILEFIRE_HPP
	#define INDIE_STUDIO_TILEFIRE_HPP

#include <chrono>
#include "ABiomeTile.hpp"

class TileFire : public ATile
{
public:
	explicit TileFire(BiomeManager::Name biome, double x ,double y, bool wasSoft, Type type = FIRE);
	bool isFinish() const;
	bool isSoft() const;
	void draw(irr::s32 x, irr::s32 y, irr::s32 titleSize) override;
	~TileFire() override;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _t;
	irr::scene::ILightSceneNode *light;
	bool _wasSoft;
	irr::scene::IAnimatedMeshSceneNode *wall;
	irr::scene::IParticleSystemSceneNode *ps;
	double lightX;
	double lightY;
};

#endif //INDIE_STUDIO_TILEFIRE_HPP
