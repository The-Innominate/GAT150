#pragma once
#include "Framework/Actor.h"

class Enemy : public kda::Actor {
public:
	Enemy(float speed, float turnRate, const kda::Transform& transform) :
		Actor{ transform },
		speed{ speed },
		turnRate{ turnRate }
	{
		m_fireTime = 2.0f;
		m_fireRate = m_fireTime;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void onCollision(Actor* actor) override;

private:
	float speed = 0;
	float turnRate = 0;

	float m_fireTime = 3.0f;
	float m_fireRate = 0;
	int hp = 10;
};