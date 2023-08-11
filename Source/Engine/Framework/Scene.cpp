#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"

void kda::Scene::Update(float dt){
	//for (auto& actor : m_actors) {
	//	actor->Update(dt);
	//}

	//update and remove destroyed actors
	auto iter = m_actors.begin();
	while (iter != m_actors.end()) {
		(*iter)->Update(dt);
		((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;
	}

	//check collisions
	for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
		for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {

			CollisionComponent* collision = (*iter1)->GetComponent<CollisionComponent>();
			CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

			if(!collision || !collision2) continue;

			if (collision->CheckCollision(collision2)) {
				(*iter1)->onCollision(iter2->get());
				(*iter2)->onCollision(iter1->get());
			}
		}
	}
}

void kda::Scene::Draw(Renderer& renderer){
	for (auto& actor : m_actors) {
		actor->Draw(renderer);
	}
}

void kda::Scene::Add(std::unique_ptr<Actor> actor){
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

void kda::Scene::RemoveAll(){
	m_actors.clear();
}
