#include "JumpyGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Framework/Emitter.h"
#include "Player.h"
#include "Framework/Components/TextRenderComponent.h"



bool JumpyGame::Initialize() {
	//m_gameOverText->Create(kda::g_renderer, "GAME OVER", kda::Color{ 1, 1, 1, 1 });
	//Load audio
	//kda::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Load("Scenes/JumpyScene.json");
	m_scene->Initialize();

	
	EVENT_SUBSCRIBE("AddPoints", JumpyGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", JumpyGame::OnPlayerDead);
	EVENT_SUBSCRIBE("GameOver", JumpyGame::GameOver);

	kda::g_audioSystem.AddAudio("dead", "Audio/dead.wav");

	return true;
}

void JumpyGame::Shutdown() {

}

bool died = false;
void JumpyGame::Update(float dt) {
	switch (m_state)
	{
	case JumpyGame::eState::Title:
	{
		/*int i = 0;
		i++;
		dt = kda::g_time.getDeltaTime();
		if (dt <= i) {
			auto actor = INSTANTIATE(Actor, "Box");
			actor->transform.position = { kda::random(kda::g_renderer.GetWidth()), 100};
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}*/
		kda::g_audioSystem.PlayOneShot("dead", true);
		if(!died){
			m_scene->GetActorByName("Title")->GetComponent<kda::TextRenderComponent>()->SetText("Falling Down?");
		}
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_score = 0;
			m_state = eState::StartGame;
		}
	}
		break;
	case JumpyGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case JumpyGame::eState::StartLevel:
		{
			if (!m_scene->GetActorByName("Player")) {
				auto actor = INSTANTIATE(Actor, "Player");
				actor->Initialize();
				m_scene->Add(std::move(actor));
			}
			
		}
		
		m_state = eState::Game;
		break;
	case JumpyGame::eState::Game:
		m_spawnTime = 4;
		if (m_score >= 1000) {
			m_spawnTime = 3;
		}if (m_score >= 2000) {
			m_spawnTime = 2;	
		}if (m_score >= 3000) {
			m_spawnTime = 1;
		}if (m_score >= 4000) {
			m_spawnTime = 0.5;	
		}if (m_score >= 5000) {
			m_spawnTime = 0.25;
		}if (m_score >= 6000) {
			m_spawnTime = 0.1;
		}
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			auto actor = INSTANTIATE(Actor, "Enemy");
			actor->transform.position = { kda::random(kda::g_renderer.GetWidth()), 500 };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (!m_scene->GetActorByName("Player")) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case JumpyGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case JumpyGame::eState::GameOver:
		m_stateTimer = 3;
		m_stateTimer -= dt;
			
		if (m_stateTimer <= 0) {
			m_scene->GetActorByName("Title")->GetComponent<kda::TextRenderComponent>()->SetText("GAME OVER");
			died = true;
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void JumpyGame::Draw(kda::Renderer& renderer) {
	
	if (m_state == eState::Title) {
		//m_titleText->Draw(renderer, 400, 300);
		m_scene->GetActorByName("Title")->active = true;
	}else {
		m_scene->GetActorByName("Title")->active = false;
	}
	m_scene->Draw(renderer);
	
}

void JumpyGame::AddPoints(const kda::Event& event) {
	m_score += std::get<int>(event.data);
	if (m_scene->GetActorByName("Player") == nullptr) {
		m_score = 0;
	}
	m_scene->GetActorByName("Score")->GetComponent<kda::TextRenderComponent>()->SetText("Score: " + std::to_string(m_score));
}

void JumpyGame::OnPlayerDead(const kda::Event& event) {
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

void JumpyGame::GameOver(const kda::Event& event)
{
	m_scene->GetActorByName("Player")->m_destroyed = true;
	m_score = 0;
	m_scene->GetActorByName("Title")->GetComponent<kda::TextRenderComponent>()->SetText("GAME OVER");
	died = true;
	m_state = eState::Title;
	
}

// Path: Source\Game\Game\JumpyGame.cpp
