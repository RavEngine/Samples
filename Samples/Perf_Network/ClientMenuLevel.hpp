#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/SharedObject.hpp>

class ClientMenu : public RavEngine::World {
public:
	void ConnectToServer(const std::string& addr, uint16_t port);
	void OnActivate() final;
};
