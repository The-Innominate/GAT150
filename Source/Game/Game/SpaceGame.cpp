#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ModelManager.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Framework/Emitter.h"

bool SpaceGame::Initialize(){
	//Create fonts/ text objects
	m_font = std::make_shared<kda::Font>("MetalRocker.ttf", 24);
	m_scoreText = std::make_unique<kda::Text>(m_font);
	m_scoreText->Create(kda::g_renderer, "0000", kda::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<kda::Text>(m_font);
	m_titleText->Create(kda::g_renderer, "AZTEROIDS", kda::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<kda::Text>(m_font);
	m_gameOverText->Create(kda::g_renderer, "GAME OVER", kda::Color{ 1, 1, 1, 1 });
	//Load audio
	kda::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();

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
		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kda::pi, kda::Transform{ {400, 300}, 10, 3 }, kda::g_modelManager.get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kda::randomf(75.0f, 150.0f), kda::pi, kda::Transform((float)(kda::random(800), kda::random(600)), (float)kda::random((int)(kda::pi2), 1)), kda::g_modelManager.get("Enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
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
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}

// Path: Source\Game\Game\SpaceGame.cpp
