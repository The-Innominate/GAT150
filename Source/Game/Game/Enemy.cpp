#include "Enemy.h"
#include "Player.h"
#include "Pew.h"
#include "SpaceGame.h"
#include "./Framework/Scene.h"
#include "Render/Renderer.h"
#include "Render/ModelManager.h"
#include <Framework/Emitter.h>

void Enemy::Update(float dt) {

	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		kda::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.angle() + kda::halfpi;
	}

	kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kda::g_time.getDeltaTime();
	m_transform.position.x = kda::wrap(m_transform.position.x, (float)kda::g_renderer.GetWidth());
	m_transform.position.y = kda::wrap(m_transform.position.y, (float)kda::g_renderer.GetHeight());

	m_fireRate -= dt;
	if (m_fireRate <= 0) {
		kda::Transform transform1{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Pew> pew = std::make_unique<Pew>(400.0f, transform1, kda::g_modelManager.get("EnemyBullet.txt"));
		pew->m_tag = "Enemy";
		m_scene->Add(std::move(pew));

		m_fireRate = m_fireTime;
	}
	
}

void Enemy::onCollision(Actor* actor){
	//Player* p = dynamic_cast<Player*>(actor)
	if (actor->m_tag == "Player") {
		hp -= 5;
	}
	if (hp <= 0) {
		m_game->AddPoint(100);
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
		kda::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<kda::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}
