#pragma once
#include "RenderComponent.h"
#include "Render/Model.h"

namespace kda {
	
	class ModelRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(ModelRenderComponent)

			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;

			virtual float getRadius() override {return m_model->getRadius();}
		public:
			res_t<Model> m_model;
	};
}