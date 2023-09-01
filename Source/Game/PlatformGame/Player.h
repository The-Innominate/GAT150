#pragma once
#include "./Framework/Actor.h"
#include "./Framework/Components/PhysicsComponents.h"
#include "Framework/Components/SpriteAnimComponent.h"

namespace kda
{
	class Player : public kda::Actor {
	public:
		CLASS_DECLARATION(Player)
		
		bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;
		void onCollisionExit(Actor* actor) override;

	private:
		float speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int hp = 20;
		int groundCount = 0;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
		kda::SpriteAnimComponent* m_spriteAnimComponent = nullptr;
	};
}