#pragma once
#include "./Framework/Actor.h"
#include "./Framework/Components/PhysicsComponents.h"

class Player : public kda::Actor {
	public:
		Player(float speed, float turnRate, const kda::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{}

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor) override;

	private:
		float speed = 0;
		float turnRate = 0;
		int hp = 100;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
};