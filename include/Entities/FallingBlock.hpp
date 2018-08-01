/*
** EPITECH PROJECT, 2018
** FallingBloc
** File description:
** Declaration of FallingBloc
*/

#ifndef INDIE_STUDIO_FALLINGBLOC_HPP
	#define INDIE_STUDIO_FALLINGBLOC_HPP

#include "AEntity.hpp"

class FallingBlock
{
public:
	FallingBlock(BiomeManager::Name resName, irr::core::vector3df &pos, int, size_t , size_t);
	void createBlock(Map &map, std::vector<AEntity *> &entities);
	void down(Map &map, std::vector<AEntity *> &entities);
	bool isIsDown() const;
	virtual ~FallingBlock();
private:
	irr::scene::IAnimatedMesh *animatedMesh;
	irr::scene::IAnimatedMeshSceneNode *animatedMeshSceneNode;
	int tileSize;
	size_t destructedX;
	size_t destructedY;
	BiomeManager::Name name;
	bool isDown;
};

#endif //INDIE_STUDIO_FALLINGBLOC_HPP
