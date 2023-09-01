#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Framework/Emitter.h"

bool SpaceGame::Initialize(){
	//Create fonts/ text objects
	//m_font = kda::g_resources.Get<kda::Font>("MetalRocker.ttf", 24);
	m_font = GET_RESOURCE(kda::Font, "MetalRocker.ttf", 24);
	m_scoreText = std::make_unique<kda::Text>(GET_RESOURCE(kda::Font, "MetalRocker.ttf", 24));
	m_scoreText->Create(kda::g_renderer, "0000", kda::Color{ 1, 1, 1, 1 });

	/*m_titleText = std::make_unique<kda::Text>(GET_RESOURCE(kda::Font, "MetalRocker.ttf", 24));
	m_titleText->Create(kda::g_renderer, "AZTEROIDS", kda::Color{ 1, 1, 1, 1 });*/

	m_gameOverText = std::make_unique<kda::Text>(m_font);
	m_gameOverText->Create(kda::g_renderer, "GAME OVER", kda::Color{ 1, 1, 1, 1 });
	//Load audio
	kda::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scenes/SpaceScene.json");
	m_scene->Initialize();


	EVENT_SUBSCRIBE("AddPoints", SpaceGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt){

	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			//m_scene->GetActorByName("Background")->active = false;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		auto player = INSTANTIATE(Player, "Player");
		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scoreText->Create(kda::g_renderer, "Score " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kda::Renderer& renderer){
	if (m_state == eState::Title) {
		//m_titleText->Draw(renderer, 400, 300);
		m_scene->GetActorByName("Title")->active = true;
	}else {
		m_scene->GetActorByName("Title")->active = false;
	}

	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scene->Draw(renderer);
	m_scoreText->Draw(renderer, 40, 20);
}

void SpaceGame::AddPoints(const kda::Event& event){
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kda::Event& event){
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

// Path: Source\Game\Game\SpaceGame.cpp
