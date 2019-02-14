#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include <algorithm>
#include "../Animation.h"



class AISystem
{
	std::vector<Entity *> m_entities;

	struct Line
	{
		float x1;
		float y1;
		float x2;
		float y2;
	};

public:
	AISystem();
	void addEntity(Entity * e);
	void update();
	c2v checkClosest(std::vector<std::pair<double, c2v>> distances, std::pair<double, c2v > real);
	double distance(c2v  vecOne, c2v vecTwo);
	std::pair<c2v, std::string> checkPoints(std::vector<std::pair<c2v, std::string>> walkpoints, PositionComponent* pc);
	void receive(std::vector<Entity*> ents);

	void recieveLevel(std::vector<std::pair<c2v, std::string>> walkpoints, std::vector<std::pair<c2v, std::string>> jumpPoints, int width, int height);
	c2v getPosition(Entity * ent);

private:
	
	std::vector<std::pair<double, c2v>> m_dist;
	
	Animation *fsm;
	c2v m_position;

	std::vector<std::pair<c2v, std::string>> m_pathPoints;
	std::vector<std::pair<c2v, std::string>> m_jumpPoints;
	int m_height;
	int m_width;
};



#endif // !AISYSTEM_H
