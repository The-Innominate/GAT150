#pragma once
#include "Object.h"
#include "../Core/Core.h"
#include "Components/Component.h"
#include <memory>


namespace kda {
	class Renderer;

	class Actor : public Object {
		public:
			CLASS_DECLARATION(Actor)

			Actor() = default;
			Actor(const Transform& transform) :
				transform{ transform }
			{}
			Actor(const Actor& other);
			virtual ~Actor() {
				OnDestroy();
			}

			virtual bool Initialize() override;
			virtual void OnDestroy() override;

			virtual void Update(float dt);
			virtual void Draw(Renderer& renderer);

			void AddComponent(std::unique_ptr<Component> component);
			template<typename T>
			T* GetComponent();

			float GetRadius() { return 30.0f; }
			virtual void onCollisionEnter(Actor* other) {}
			virtual void onCollisionExit(Actor* other) {}
			
			friend class Scene;
			class Scene* m_scene = nullptr;
			class Game* m_game = nullptr;
			
		public:
			Transform transform;
			std::string tag;
			float lifespan = -1.0f;
			bool destroyed = false;
			bool persistent = false;
			bool prototype = false;
			int score = 0;
			bool m_destroyed = false;

		protected:
			std::vector<std::unique_ptr<class Component>> components;

			
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}
}
