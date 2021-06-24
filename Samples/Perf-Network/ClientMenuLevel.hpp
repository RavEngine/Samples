#pragma once
#include <RavEngine/World.hpp>

static constexpr auto PORT = 6970;

class ClientMenu : public RavEngine::World {
public:
	void ConnectToServer(const std::string& addr);
	void OnActivate() final;
};