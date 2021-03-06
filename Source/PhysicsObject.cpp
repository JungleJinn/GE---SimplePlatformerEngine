#include "PhysicsObject.h"

using namespace SPE;

unsigned int PhysicsObject::nextFreeId = 0;

PhysicsObject::PhysicsObject()
{
	currentForce = position = velocity = glm::vec2(0, 0);
	lastVelocity = acceleration = glm::vec2(0,0);
	//orientation = angularVelocity = 0;
	mass = 1;
	coeffOfRestitution = 1.0f;
	coeffOfFriction = 0.9f;
	lastDeltaTime = 0;
	lastCollisionObject = collisionObject = NULL;

	useGravity = true;
	physicsActive = true;
}

PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::Integrate(float deltaTime)
{
	if (useGravity)
		AddForce(glm::vec2(0, GRAVITY) * mass);

	if (mass != 0)
	{
		// integrate acceleration and velocity
		acceleration = currentForce / mass;
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;

		// integrate angular acceleration and velocity
		//TODO acceleration
		//orientation += angularVelocity * deltaTime;
	}
	// set stuff for next frame

	// store velocity
	lastVelocity = velocity;
	// store deltatime
	lastDeltaTime = deltaTime;
	// reset force
	currentForce = glm::vec2(0, 0);
	// reset collisionobject
	lastCollisionObject = collisionObject;
	collisionObject = NULL;
}

// implements collision response
// based on "Physics for Game Developers", David M. Bourg, Chapters 5 and 13
void PhysicsObject::Collide(PhysicsObject* other, glm::vec2 normal)
{
	collisionObject = other;

	glm::vec2 relativeVelocity = this->velocity - other->velocity;
	float cosCollAngle = glm::dot(relativeVelocity, normal);

	// the objects are moving away from each other - stuck in each other
	if (cosCollAngle > 0)
	{
		// make them move out of each other depending on their distance
		glm::vec2 distanceV = this->position - other->position;
		float enhanceFactor = 1 / sqrt(distanceV.x * distanceV.x + distanceV.y * distanceV.y);
		if (this->mass > 0)
		{
			this->velocity += normal * enhanceFactor * lastDeltaTime;
		}
		if (other->mass > 0)
		{
			other->velocity += normal * enhanceFactor * lastDeltaTime;
		}
		return;
	}
	// objects are moving towards each other (or in contact)
	else
	{
		// friction
		if (collisionObject == lastCollisionObject && collisionObject != NULL)
		{
			// only use friction when there is a collision
			float friction = 0;
			friction = (this->coeffOfFriction + collisionObject->coeffOfFriction) * 0.5f;
			AddForce(-glm::normalize(lastVelocity) * friction);
		}

		// calculate shared bounciness
		float newCoeffOfRestitution = 
			-(1 + (coeffOfRestitution + other->coeffOfRestitution) * 0.5f);

		// bounce away from other object and make the other one bounce away from me
		float temp1 = relativeVelocity.x * normal.x + 
			relativeVelocity.y * normal.y;
		float temp2 = normal.x * normal.x + normal.y * normal.y;
		
		float responseStrength =
			(newCoeffOfRestitution * glm::dot(relativeVelocity, normal)) /
			( glm::dot(normal, normal) * 
			// hack for infinite/zero mass objects
			(1 / (this->mass != 0 ? this->mass : 1000000) + 1 / 
			(other->mass != 0 ? other->mass : 1000000)));

		if (this->mass != 0)
		{
			this->velocity += (normal * responseStrength) / this->mass;
		}

		if (other->mass != 0)
		{
			other->velocity -= (normal * responseStrength) / other->mass;
		}
	}
}

void PhysicsObject::AddForce(glm::vec2 force)
{
	currentForce += force;
}
