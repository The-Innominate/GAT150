#include "SpriteComponent.h"
#include "Render/Render.h"
#include "Framework/Actor.h"
#include "Framework/ResourceManager.h"

namespace kda {
	CLASS_DEFINITION(SpriteComponent);

	bool SpriteComponent::Initialize()
	{
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void kda::SpriteComponent::Update(float dt){

	}

	void kda::SpriteComponent::Draw(Renderer& renderer){
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}

