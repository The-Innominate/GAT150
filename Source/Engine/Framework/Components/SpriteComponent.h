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

		public:
			std::string textureName;
			Rect source;
			bool flipH = false;
			vec2 origin { .5f , .5f };

			res_t<Texture> m_texture;
	};
}