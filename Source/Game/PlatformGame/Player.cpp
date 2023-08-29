#include "Player.h"
#include "Render/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"

namespace kda {

	CLASS_DEFINITION(Player)

		bool Player::Initialize() {
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<kda::PhysicsComponent>();
		

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		//movement
		float dir = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) dir = -1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) dir = 1;
		
		kda::vec2 forward = kda::vec2{ 1 , 0 };
		m_physicsComponent->ApplyForce(forward * speed * dir);

		//Jump
		bool onGround = (groundCount > 0);

		if (onGround && kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)
			&& !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_UP)) {
			
			kda::vec2 up = kda::vec2{ 0 , -1 };
			m_physicsComponent->SetVelocity(up * jump);

		}
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "EnemyBullet") {
			hp -= 5;
		}
		if (actor->tag == "Enemy") {
			m_destroyed = true;
			m_game->SetLives(m_game->GetLives() - 1);
		}
		if (actor->tag == "Ground") {
			groundCount++;
		}
	}

	void Player::onCollisionExit(Actor* actor)
	{
		if (actor->tag == "Ground")
		{
			groundCount--;
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
