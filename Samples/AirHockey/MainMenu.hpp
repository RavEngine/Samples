#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>
#include <semaphore>

namespace RavEngine {
	class AudioAsset;
}

class MainMenu : public RavEngine::World, public RavEngine::IInputListener{
public:
	MainMenu();
private:
	void LoadGame(int);
	RavEngine::Entity mainMenu;
	Ref<RavEngine::AudioAsset> musicAsset;
	std::binary_semaphore musicSemaphore{ 0 };
};
