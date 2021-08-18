#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include "Level.hpp"
#include <RavEngine/Debug.hpp>
#include "NetEntity.hpp"
#include "ClientMenuLevel.hpp"

using namespace std;
using namespace RavEngine;


struct NetApp : public RavEngine::App {
	NetApp() : App(APPNAME) {}
	void OnStartup(int argc, char** argv) final {

		// must register all networked entities
		networkManager.RegisterNetworkedEntity<NetEntity>();
		networkManager.RegisterNetworkedEntity<ManagementRelay>();

		//argc = 2;

		// to start as a server, simply launch with any extra argument
		if (argc > 1) {
			this->networkManager.server = std::make_unique<NetworkServer>();
			this->networkManager.server->Start(PORT);
			Debug::Log("Started server on {}",PORT);
			AddWorld(make_shared<Level>());
		}
		// otherwise we will launch as a client
		else {
			this->networkManager.client = std::make_unique<NetworkClient>();
			AddWorld(make_shared<ClientMenu>());

			Debug::Log("Started client on {}", PORT);
		}

		SetWindowTitle(StrFormat("{} {} | {}", APPNAME, networkManager.IsServer()? "Server" : "Client", Renderer->GetCurrentBackendName()).c_str());
	}
};
START_APP(NetApp)