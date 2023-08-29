#pragma once
#include "./Framework/Actor.h"
#include "./Framework/Components/PhysicsComponents.h"

namespace kda
{
	class Enemy : public kda::Actor {
	public:
		CLASS_DECLARATION(Enemy)

			bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;
		void onCollisionExit(Actor* actor) override;

	private:
		float speed = 0;
		float jump = 0;
		int hp = 20;
		int groundCount = 0;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}