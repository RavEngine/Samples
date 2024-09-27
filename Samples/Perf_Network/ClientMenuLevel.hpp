#pragma once
#if !RVE_SERVER

#include <RavEngine/World.hpp>

class ClientMenu : public RavEngine::World {
public:
	void ConnectToServer(const std::string& addr, uint16_t port);
	void OnActivate() final;
};
#endif
