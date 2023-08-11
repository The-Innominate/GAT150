#include "SpriteComponent.h"
#include "Render/Render.h"
#include "Framework/Actor.h"

namespace kda {
	void kda::SpriteComponent::Update(float dt){

	}

	void kda::SpriteComponent::Draw(Renderer& renderer){
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}

