#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include "../cute_c2.h"

class PositionComponent : public Component
{
public:
	PositionComponent(float x, float y) : x(x), y(y){}

	float getX() { return x; }
	float getY() { return y; }


	void setX(float x) { this->x = x; }
	void setY(int y) { this->y = y; }

	float getVelX() { return vel.x; }
	float getVelY() { return vel.y; }


	void setVelX(float x) { 
		vel.x = x; 
	}
	void setVelY(float y) { vel.y = y; }

	std::string m_tag = "POSITION";

	std::string getType() { return m_tag; }

	c2v vel = { 0,0 };
	
private:
	float x;
	float y;

};
#endif // !POSITIONCOMPONENT_H