#pragma once
#include <RavEngine/World.hpp>

static constexpr auto PORT = 6970;

class ClientMenu : public RavEngine::World, public RavEngine::virtual_enable_shared_from_this<ClientMenu> {
public:
	void ConnectToServer(const std::string& addr);
	void OnActivate() final;
};
