#include "JumpyGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Framework/Emitter.h"


bool JumpyGame::Initialize() {
	//m_gameOverText->Create(kda::g_renderer, "GAME OVER", kda::Color{ 1, 1, 1, 1 });
	//Load audio
	//kda::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scenes/JumpyScene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();


	EVENT_SUBSCRIBE("AddPoints", JumpyGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", JumpyGame::OnPlayerDead);

	return true;
}

void JumpyGame::Shutdown() {

}

void JumpyGame::Update(float dt) {

	switch (m_state)
	{
	case JumpyGame::eState::Title:
	{
		/*auto actor = INSTANTIATE(Actor, "Box");
		actor->transform.position = { kda::random(kda::g_renderer.GetWidth()), 100};
		actor->Initialize();
		m_scene->Add(std::move(actor));*/
	}
		break;
	case JumpyGame::eState::StartGame:
		
		break;
	case JumpyGame::eState::StartLevel:
		
		break;
	case JumpyGame::eState::Game:
		
		break;
	case eState::PlayerDeadStart:
		
		break;
	case JumpyGame::eState::PlayerDead:
		
		break;
	case JumpyGame::eState::GameOver:
		
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void JumpyGame::Draw(kda::Renderer& renderer) {
	
	m_scene->Draw(renderer);
	
}

void JumpyGame::AddPoints(const kda::Event& event) {
	m_score += std::get<int>(event.data);
}

void JumpyGame::OnPlayerDead(const kda::Event& event) {
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

// Path: Source\Game\Game\JumpyGame.cpp
