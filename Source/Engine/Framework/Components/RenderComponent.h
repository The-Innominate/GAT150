#pragma once
#include "Component.h"

namespace kda {
	class RenderComponent : public Component {
		public :
			virtual void Draw(class Renderer& renderer) = 0;
			virtual float getRadius() = 0;
	};
}