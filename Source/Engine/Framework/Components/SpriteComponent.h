#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Framework/Factory.h"
#include <Render/Texture.h>

namespace kda {
	class SpriteComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(SpriteComponent)

			bool Initialize() override;
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;

			virtual float getRadius() override { return m_texture->GetSize().length() * 0.5f; }

		public:
			std::string textureName;
			res_t<Texture> m_texture;
	};
}