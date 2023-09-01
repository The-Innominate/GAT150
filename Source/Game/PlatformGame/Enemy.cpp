#include "Enemy.h"
#include "Player.h"
#include "Render/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Framework/Event/EventManager.h"


namespace kda {

	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize() {
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<kda::PhysicsComponent>();


		return true;
	}

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		//movement
		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			//kda::vec2 direction = -1;/*player->transform.position - transform.position;*/
			//m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}
	}

	void Enemy::onCollisionEnter(Actor* actor) {
		if (actor->tag != "Enemy") {
			kda::EventManager::Instance().DispatchEvent("AddPoints", 100);
			Player* player = m_scene->GetActor<Player>();
			if (player)
			{
				float distance = player->transform.position.x - transform.position.x;
				if (std::fabs(distance) < 30)
				{
					player->destroyed = true;
					kda::EventManager::Instance().DispatchEvent("GameOver", 0);
					
				}
			}
			m_destroyed = true;
		}
	}

	void Enemy::onCollisionExit(Actor* actor)
	{
	
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
