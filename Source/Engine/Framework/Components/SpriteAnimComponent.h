#pragma once
#include "Framework/Components/SpriteComponent.h"

namespace kda {
	class SpriteAnimComponent : public SpriteComponent {
	public:
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};
	public:
		CLASS_DECLARATION(SpriteAnimComponent)

		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& name);
		void UpdateSource();

	public:
		int frame = 0;
		float frameTime = 0;

	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> sequences;
		AnimSequence* m_sequence = nullptr;
	};
}