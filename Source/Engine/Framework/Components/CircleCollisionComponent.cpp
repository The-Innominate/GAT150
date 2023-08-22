#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kda{

	CLASS_DEFINITION(CircleCollisionComponent)

	void kda::CircleCollisionComponent::Update(float dt){

	}

	bool kda::CircleCollisionComponent::CheckCollision(CollisionComponent* collision){
		float distance = m_owner->transform.position.distance(collision->m_owner->transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}

	void CircleCollisionComponent::Read(const json_t& value) {
		//
	}
}
