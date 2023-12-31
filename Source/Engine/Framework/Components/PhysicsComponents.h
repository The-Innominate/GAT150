#pragma once
#include "Component.h"
#include <Core/Math/Vector2.h>

namespace kda {
	class PhysicsComponent : public Component{

		public:
			//void Update(float dt) override;
			virtual void ApplyForce(const vec2& force) = 0;
			virtual void ApplyTorque(float torque) = 0;

		public:
			vec2 m_velocity;
			vec2 m_acceleration;
			float m_mass = 1.0f;
			float m_damping = 0;
	};
}