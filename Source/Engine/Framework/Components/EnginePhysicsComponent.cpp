#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace kda {
	CLASS_DEFINITION(EnginePhysicsComponent)

	void kda::EnginePhysicsComponent::Update(float dt){
		m_owner->transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void kda::EnginePhysicsComponent::ApplyForce(const vec2& force){
		m_velocity += force;
	}

	void EnginePhysicsComponent::ApplyTorque(float torque)
	{
		//
	}

	void EnginePhysicsComponent::Read(const json_t& value) {
		//
	}
}
