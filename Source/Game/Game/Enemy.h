#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"


namespace kda {
	class Enemy : public kda::Actor {
	public:
		CLASS_DECLARATION(Enemy)
		/*Enemy(float speed, float turnRate, const kda::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{
			m_fireTime = 2.0f;
			m_fireRate = m_fireTime;
		}*/

		bool Initialize() override;

		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;

	private:
		float speed = 0;
		float turnRate = 0;

		float m_fireTime = 3.0f;
		float m_fireRate = 0;
		int hp = 10;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}