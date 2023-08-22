#pragma once
#include "Framework/Framework.h"
#include "Core/Json.h"

namespace kda {

	class Pew : public Actor {
	public:
		CLASS_DECLARATION(Pew)
		/*
		Pew(float speed, const kda::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		}
		*/

		bool Initialize() override;

		void Update(float dt) override;
		void onCollision(Actor* actor) override;
		//void Read(const json_t& value);

	private:
		float speed = 0;
		float turnRate = 0;
	};
}