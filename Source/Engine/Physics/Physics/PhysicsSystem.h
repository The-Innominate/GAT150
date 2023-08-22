#pragma once
#include "Framework/Singleton.h"
#include "box2d/include/box2d/b2_world.h"		//<include b2_world.h from the box2d directory>
#include <memory>

namespace kda {

	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
		public:
			bool Initialize();
			void Update(float dt);

			friend class Singleton;
		private:
			//<declare default constructor>
			PhysicsSystem() = default;
		private:
			//<unique pointer of b2World> m_world;
			std::unique_ptr<b2World> m_world;
	};
}