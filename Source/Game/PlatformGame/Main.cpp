#include "JumpyGame.h"

#include "Render/Render.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Render/Texture.h"
#include "Core/Core.h"
#include "../../Engine/Core/Math/Vector2.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Physics/Physics/PhysicsSystem.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <array>
#include <functional>

using namespace std;


void zero(int v) {
	v = 0;
}

template <typename T>
void print(const std::string& s, const T& container)
{
	std::cout << s << std::endl;
	for (auto element : container)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}


int main(int argc, char* argv[]) {

	INFO_LOG("Initialize Engine...");

	kda::MemoryTracker::Initialize();
	kda::seedRandom((unsigned int)time(nullptr));
	kda::setFilePath("Assets");

	//Initialize game engine
	kda::g_audioSystem.Initialize();
	kda::g_renderer.Initialize();
	kda::g_renderer.CreateWindow("CSC196", 800, 600);
	kda::g_inputSystem.Initialize();
	kda::PhysicsSystem::Instance().Initialize();

	unique_ptr<JumpyGame> game = make_unique<JumpyGame>();
	game->Initialize();


	// Main game loop
	bool quit = false;
	while (!quit) {

		kda::g_audioSystem.Update();
		kda::g_time.tick();
		kda::g_inputSystem.Update();
		kda::g_particleSystem.Update(kda::g_time.getDeltaTime());
		kda::PhysicsSystem::Instance().Update(kda::g_time.getDeltaTime());

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		//Update Game
		game->Update(kda::g_time.getDeltaTime());

		kda::g_renderer.SetColor(0, 0, 0, 0);
		kda::g_renderer.BeginFrame();

		//draw
		game->Draw(kda::g_renderer);
		kda::g_particleSystem.Draw(kda::g_renderer);

		
		//model.Draw(kda::g_renderer, transform.position, transform.scale, transform.rotation);

		kda::g_renderer.EndFrame();
	}

	return 0;

}