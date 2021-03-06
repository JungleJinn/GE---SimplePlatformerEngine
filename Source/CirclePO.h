#ifndef CIRCLEPO_H
#define CIRCLEPO_H

#include <glm/glm.hpp>

#include "PhysicsObject.h"
#include "RectanglePO.h"

namespace SPE
{
	// a circular physics object
	public class CirclePO : public PhysicsObject
	{
	public:
			
		bool				TestCollision(PhysicsObject* other);
		Shape				GetShape();

		virtual void		OnCollision(PhysicsObject *o1, PhysicsObject *o2) = 0;
	};
};

#endif
