#include "ModelManager.h"

namespace kda {
	ModelManager g_modelManager;

	std::shared_ptr<Model> ModelManager::get(const std::string& filename)
	{
		if (m_models.find(filename) == m_models.end()) {
			std::shared_ptr<Model> model = std::make_shared<Model>();
			model->load(filename);

			m_models[filename] = model;
		}

		return m_models[filename];
	}
}