#include "Player.h"
#include "Framework/Scene.h"
#include "Render/Renderer.h"
#include "Pew.h"
#include "SpaceGame.h"
#include <Framework/Emitter.h>
#include "Render/ModelManager.h"

void Player::Update(float dt) {
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kda::g_time.getDeltaTime();

	float thrust = 0;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP))thrust = 1;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) {
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
		data.color = kda::Color{ 0, 1, 0, 1 };
		kda::Transform transform{ { m_transform.position } , 0, 2 };
		auto emitter = std::make_unique<kda::Emitter>(transform, data);
		emitter->m_lifespan = 0;
		m_scene->Add(std::move(emitter));
	}
		

	kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	addForce(forward * m_speed * thrust);
	

	//m_transform.position += forward * m_speed * thrust * kda::g_time.getDeltaTime();
	m_transform.position.x = kda::wrap(m_transform.position.x, (float)kda::g_renderer.GetWidth());
	m_transform.position.y = kda::wrap(m_transform.position.y, (float)kda::g_renderer.GetHeight());

	//fire weapon
	int weaponSelect = 1;

	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_1)) weaponSelect = 1;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_2)) weaponSelect = 2;
		
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) 
		&& !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

		if (weaponSelect == 1) {
			kda::Transform transform1{m_transform.position, m_transform.rotation, 1};
			std::unique_ptr<Pew> pew = std::make_unique<Pew>(400.0f, transform1, kda::g_modelManager.get("PlayerBullet.txt"));
			pew->m_tag = "Player";
			m_scene->Add(std::move(pew));
		}

		//Create Weapon
		if (weaponSelect == 2) {
			kda::Transform transform1{m_transform.position, m_transform.rotation + kda::DegreesToRadians(5.0f), 1};
			std::unique_ptr<Pew> pew = std::make_unique<Pew>( 400.0f, transform1, kda::g_modelManager.get("PlayerBullet.txt"));
			pew->m_tag = "Player";
			m_scene->Add(std::move(pew));

			kda::Transform transform2{m_transform.position, m_transform.rotation - kda::DegreesToRadians(5.0f), 1};
			std::unique_ptr<Pew> pew2 = std::make_unique<Pew>(400.0f, transform2, kda::g_modelManager.get("PlayerBullet.txt"));
			pew2->m_tag = "Player";
			m_scene->Add(std::move(pew2));
		}
		
	}

	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
	else kda::g_time.setTimeScale(1.0f);
}

void Player::onCollision(Actor* actor){
	if (actor->m_tag == "EnemyBullet") {
		hp -= 5;
	}
	if (actor->m_tag == "Enemy") {
		m_destroyed = true;
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}
}