#pragma once
#include <RavEngine/World.hpp>

class ClientMenu : public RavEngine::World, public RavEngine::virtual_enable_shared_from_this<ClientMenu> {
public:
	void ConnectToServer(const std::string& addr, uint16_t port);
	void OnActivate() final;
};
