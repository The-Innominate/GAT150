#include "Enemy.h"
#include "Player.h"
#include "Pew.h"
#include "SpaceGame.h"
#include "Render/Renderer.h"
#include "Framework/Framework.h"


namespace kda {

	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize() {

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


	void Enemy::Update(float dt) {

		Actor::Update(dt);
		kda::Vector2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			kda::Vector2 direction = player->transform.position - transform.position;
			float turnAngle = kda::vec2::SignedAngle(forward, direction.Normalized());
			//transform.rotation = direction.angle() + kda::halfpi;
			m_physicsComponent->ApplyTorque(turnAngle);
		}


		m_physicsComponent->ApplyForce(forward * speed);
		//transform.position += forward * speed * kda::g_time.getDeltaTime();
		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());

		/*m_fireRate -= dt;
		if (m_fireRate <= 0) {
			kda::Transform transform1{transform.position, transform.rotation, 1};
			std::unique_ptr<WeaponComponent> pew = std::make_unique<WeaponComponent>(400.0f, transform1);
			pew->tag = "Enemy";

			std::unique_ptr<kda::SpriteComponent> component = std::make_unique<kda::SpriteComponent>();
			component->m_texture = GET_RESOURCE(kda::Texture, "EnemyBullet.png", kda::g_renderer);
			pew->AddComponent(std::move(component));

			m_scene->Add(std::move(pew));

			m_fireRate = m_fireTime;
		}*/

	}

	void Enemy::onCollision(Actor* actor) {
		//Player* p = dynamic_cast<Player*>(actor)
		if (actor->tag == "Player") {

			hp -= 5;
		}
		if (hp <= 0 && !m_destroyed) {
			//m_game->AddPoint(100);
			kda::EventManager::Instance().DispatchEvent("AddPoints", 100);
			m_destroyed = true;

			kda::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kda::pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = kda::Color{ 1, 0, 0, 1 };
			kda::Transform transform{ this->transform.position, 0, 1 };
			auto emitter = std::make_unique<kda::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));

		}
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, hp);
	}
}
