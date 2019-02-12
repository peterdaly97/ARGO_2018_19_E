#include "AISystem.h"

AISystem::AISystem() {
	fsm = new Animation();
}

void AISystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AISystem::receive(std::vector<Entity*> ents)
{
	int count = 0;
	c2v vec = { 0.0f, 0.0f };
	m_distances.assign(ents.size(), std::make_pair(0.0, vec));
	
	for (auto e = ents.begin(); e != ents.end(); ++e)
	{
		PositionComponent  * pos = (PositionComponent*)(*e)->getCompByType("POSITION");
		ControlComponent * con = (ControlComponent*)(*e)->getCompByType("CONTROL");
		AIComponent * ac = (AIComponent*)(*e)->getCompByType("AI");
		
		
		m_distances[count].first = ac->distance(curPosition, pos->getX(), pos->getY());
			
		vec.x = pos->getX();
		vec.y = pos->getY();
			
		m_distances[count].second = vec;
		
		count++;
	}	
}

c2v AISystem::checkClosest(std::vector<std::pair<double, c2v>> distances)
{

	double smallest = 10000;

	for (auto it = distances.begin(); it != distances.end(); it++)
	{
		if (it->first != 0)
		{
			if (it->first < smallest) {
				smallest = it->first;
				m_realDist = (*it);
			}
		}
	}
	
	//need to fix to find closest;
	return m_realDist.second;
}

c2v AISystem::checkJumpPoints(std::vector<c2v*> points, PositionComponent* pc)
{

	double smallest = 10000;

	c2v myPos = { pc->getX(), pc->getY() };
	c2v closestPosition;
	//points = checkTier(points);
	for (auto it = points.begin(); it != points.end(); it++)
	{
		//std::cout << (*it)->x << std::endl;
		auto pos = c2v{ (*it)->x, (*it)->y };
		double dist = distance(myPos, pos);

		if (dist < smallest)
		{
			smallest = dist;
			closestPosition = pos;
		}
	}
	return closestPosition;
}

c2v AISystem::checkWalkPoints(std::vector<c2v*> points, PositionComponent* pc)
{

	double smallest = 10000;

	c2v myPos = { pc->getX(), pc->getY() };
	c2v closestPosition;
	//points = checkTier(points);
	for (auto it = points.begin(); it != points.end(); it++)
	{
		//std::cout << (*it)->x << std::endl;
		auto pos = c2v{ (*it)->x, (*it)->y };
		double dist = distance(myPos, pos);

		if (dist < smallest)
		{
			smallest = dist;
			closestPosition = pos;
			closestWalkPointDist = smallest;
		}
	}
	return closestPosition;
}

void AISystem::update(std::vector<c2v*> jumppoints, std::vector<c2v*> walkpoints) {
	
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		FState *state = (FState*)entity->getCompByType("STATE");
		//CollisionComponent *coll = (CollisionComponent*)entity->getCompByType("COLLISION");

		if (ac->m_alive) {
			curPosition.x = pc->getX();
			curPosition.y = pc->getY();

			
			newYVel = pc->getVelY();
			if (newYVel != oldYVel)
			{
				m_landed = false;
				oldYVel = newYVel;
				m_onGroundCount = 0;
			}
			else
			{
				m_landed = true;
				m_onGroundCount++;
			}
			
			std::cout << m_onGroundCount << std::endl;
			
			/*if (pc->getVelY() > 0.9 && pc->getVelY() < 1.0)
			{
				m_landed = true;
				
			}*/

			//std::cout << m_landed << std::endl;
			if (curPosition.x > closestWalkPoint.x)
			{
				facingleft = true;
				facingRight = false;
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				facingRight = true;
				facingleft = false;
				sc->m_flipValue = SDL_FLIP_NONE;
			}


			//closestEnemy = checkClosest(m_distances);
			//std::cout << curPosition.y << std::endl;
			
			if (m_landed) {
				closestJumpPoint = checkJumpPoints(jumppoints, pc);
				closestWalkPoint = checkWalkPoints(walkpoints, pc);
			}


			if (curPosition.x > closestEnemy.x)
			{
				//sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			if (curPosition.x < closestEnemy.x)
			{
				//sc->m_flipValue = SDL_FLIP_NONE;

			}
			//std::cout << closestWalkPoint.x << ", " << closestWalkPoint.y << std::endl;
			
			//std::cout << facingRight << std::endl;
			if (closestWalkPointDist <= 30)
			{
				atWalkPoint = true;
			}


			if (facingleft && m_landed)
			{
				ac->setLeft(true);
				ac->setRight(false);

				if (curPosition.x < closestWalkPoint.x + 10)
				{
					if (pc->getVelX() < -7.8)
					{
						ac->setJump(true);
					}
					else
					{
						if (m_onGroundCount > 80)
						{
							pc->setVelX(-8);
							ac->setJump(true);
						}
					}
					
				}
			}
			std::cout << facingleft << std::endl;

			if (facingRight && m_landed)
			{
				ac->setRight(true);
				ac->setLeft(false);

				if (curPosition.x > closestWalkPoint.x - 10)
				{
					if (pc->getVelX() > 7.8)
					{
						ac->setJump(true);
					
					}
					else
					{
						if (m_onGroundCount > 80)
						{
							pc->setVelX(8);
							ac->setJump(true);
						}
						
					}		
				}
			}
			

			
			//std::cout << "Vel X = " << pc->getVelX() << std::endl;
			

			//std::cout << "Point = " << closestPoint.x << ", " << closestPoint.y << std::endl;
			//std::cout << "Position = " << curPosition.x << std::endl;
		}
		
		
	}

}


double AISystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}


std::vector<c2v*> AISystem::checkTier(std::vector<c2v*> points)
{
	std::vector<c2v*> holdingVector;
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if (tierOne)
		{
			if ((*it)->y == 820)
			{
				holdingVector.push_back(*it);
			}
		}
		if (tierTwo)
		{
			if ((*it)->y == 605)
			{
				holdingVector.push_back(*it);
			}
		}
		if (tierThree)
		{
			if ((*it)->y == 395)
			{
				holdingVector.push_back(*it);
			}
		}
	}

	return holdingVector;
}

