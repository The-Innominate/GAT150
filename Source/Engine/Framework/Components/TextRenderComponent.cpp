#include "TextRenderComponent.h"
#include "Render/Text.h"
#include "Render/Font.h"
#include "Framework/ResourceManager.h"
#include "Framework/Actor.h"

namespace kda {

	CLASS_DEFINITION(TextRenderComponent)
	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other) {
		text = other.text;
		//<set font name from other font name>
		fontName = other.fontName;

		//<set font size from other font size>
		fontSize = other.fontSize;
		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}

	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty()) m_text = std::make_unique<Text>(GET_RESOURCE(Font, fontName, fontSize)/*<GET_RESOURCE with font type, font name and fontsize>)*/);
		return true;
	}

	void TextRenderComponent::Update(float dt)
	{
	}

	void TextRenderComponent::Draw(Renderer& renderer)
	{
		// update the text if changed
		if (m_changed)
		{
			m_changed = false;
			// create text using text string and color 
			m_text->Create(renderer, text, { 1, 1, 1, 1 });
		}
		// draw text
		m_text->Draw(renderer, m_owner->transform);  /*<draw using renderer and transform>*/
	}

	void TextRenderComponent::SetText(const std::string& string)
	{
		// check if text has changed, if changed set new string and update
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}

	void TextRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
	}
}