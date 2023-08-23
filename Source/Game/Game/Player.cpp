#include "Player.h"
#include "Render/Renderer.h"
#include "Pew.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Framework/Components/CollisionComponent.h"
#include "Input/InputSystem.h"

namespace kda {

	CLASS_DEFINITION(Player)

	bool Player::Initialize() {
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<kda::PhysicsComponent>();
		auto collisionComponent = GetComponent<kda::CollisionComponent>();
		if (collisionComponent) {
			auto renderComponent = GetComponent<kda::RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->getRadius() * scale;
			}
		}

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		//movement
		float rotate = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 1;
		//transform.rotation += rotate * turnRate * kda::g_time.getDeltaTime();
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) {
			thrust = 1;
			kda::EmitterData data;
			data.burst = false;
			data.burstCount = 10;
			data.spawnRate = 500;
			data.angle = 0;
			data.angleRange = kda::pi;
			data.lifetimeMin = 0.25f;
			data.lifetimeMax = 0.5f;
			data.speedMin = 25;
			data.speedMax = 50;
			data.damping = 0.5f;
			data.color = kda::Color{ 0, 0, 1, 1 };
			kda::Transform transform{ { this->transform.position }, 0, 2 };
			auto emitter = std::make_unique<kda::Emitter>(transform, data);
			emitter->lifespan = 0;
			m_scene->Add(std::move(emitter));
		}


		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);


		//transform.position += forward * speed * thrust * kda::g_time.getDeltaTime();
		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());

		//fire weapon
		int weaponSelect = 1;

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_1)) weaponSelect = 1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_2)) weaponSelect = 2;

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)
			&& !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

			auto weapon = INSTANTIATE(Pew, "Rocket");
			weapon->transform = kda::Transform{ transform.position, transform.rotation + kda::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
		}

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
		else kda::g_time.setTimeScale(1.0f);
	}

	void Player::onCollision(Actor* actor) {
		if (actor->tag == "EnemyBullet") {
			hp -= 5;
		}
		if (actor->tag == "Enemy") {
			m_destroyed = true;
			m_game->SetLives(m_game->GetLives() - 1);
			kda::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}
