/*
** EPITECH PROJECT, 2018
** Mount
** File description:
** Declaration of Mount
*/

#ifndef INDIE_STUDIO_MOUNT_HPP
	#define INDIE_STUDIO_MOUNT_HPP

#include "AEntity.hpp"

class Mount : public AEntity
{
public:
	explicit Mount(irr::core::vector3df &pos, int teamId,
		Type type = MOUNT,
		bool isMD2 = true);
	~Mount() override;
	void handleEvent(Map &map, std::vector<AEntity *> &entities) override;
	void move(const irr::core::vector3df &vec, Map &map, std::vector<AEntity *> &entities, irr::core::vector3df &oldPositions) override;
};

#endif //INDIE_STUDIO_MOUNT_HPP
