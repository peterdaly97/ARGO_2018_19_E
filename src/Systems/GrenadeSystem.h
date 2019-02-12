#ifndef GRENADESYSTEM_H
#define GRENADESYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include "../MapLoader.h"

class GrenadeSystem
{
	std::vector<Entity *> m_entities;

public:
	GrenadeSystem();
	void addEntity(Entity * e);
	void update(std::vector<std::vector<Tile*>> tiles);
	float dist(c2v v1, c2v v2);
};
#endif // !GRENADESYSTEM_H
