#pragma once
#include "Framework/Components/RenderComponent.h"

namespace kda {

	class TextRenderComponent : public RenderComponent
	{
	public:
		//<add class declaration macro>
		CLASS_DECLARATION(TextRenderComponent)
		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void SetText(const std::string& string);
	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
		Color color;
	private:
		bool m_changed = true;
		//<unique pointer of Text type> m_text;
		std::unique_ptr<class Text> m_text;
	};
}