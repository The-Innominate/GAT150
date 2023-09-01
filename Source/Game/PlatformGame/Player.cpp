#include "Player.h"
#include "Render/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"

namespace kda {

	CLASS_DEFINITION(Player)

		bool Player::Initialize() {
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);
		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->velocity;

		//movement
		float dir = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) dir = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) dir = 1;
		
		if (dir) {
			vec2 forward = vec2{ 1 , 0 };
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
			//m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.5f));
		}

		//Jump

		if (onGround && g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)
			&& !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_UP)) {
			
			kda::vec2 up = kda::vec2{ 0 , -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->setGravityScale((velocity.y > 0) ? 1.0f : .5f);

		//Animation
		if (std::fabs(velocity.x) > 0.2f) {
			if(dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else {
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "EnemyBullet") {
			hp -= 5;
		}
		if (actor->tag == "Enemy") {
			m_destroyed = true;
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
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
		READ_DATA(value, hp);
	}
}
