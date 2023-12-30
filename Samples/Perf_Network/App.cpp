#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include "Level.hpp"
#include <RavEngine/Debug.hpp>
#include "NetEntity.hpp"
#include "ClientMenuLevel.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace std;
using namespace RavEngine;

// server hosts on 6970
static constexpr auto PORT = 6970;

struct NetApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final {

		// must register all networked entities
		networkManager.RegisterNetworkedEntity<NetEntity>();
		networkManager.RegisterNetworkedEntity<ManagementRelay>();

        auto id = CTTI<NetEntity>();
        auto name = type_name<NetEntity>();
		
		//argc = 2;

		// to start as a server, simply launch with any extra argument
		if (argc > 1) {
			this->networkManager.server = std::make_unique<NetworkServer>();
			networkManager.server->OnClientConnecting = [](auto a) {
				Debug::Log("Client is connecting, id = {}",a);
			};
			networkManager.server->OnClientConnected = [](auto a) {
				Debug::Log("Client is connected, id = {}", a);
			};
			networkManager.server->OnClientDisconnected = [](auto a) {
				Debug::Log("Client disconnected, id = {}", a);
			};
			this->networkManager.server->Start(PORT);
			Debug::Log("Started server on {}",PORT);
			AddWorld(RavEngine::New<Level>());
		}
		// otherwise we will launch as a client
		else {
			this->networkManager.client = std::make_unique<NetworkClient>();
			networkManager.client->OnConnecting = [](auto a) {
				Debug::Log("Connecting to server, id = {}",a);
			};
			networkManager.client->OnConnected = [](auto a) {
				Debug::Log("Sucessfully connected to server, id = {}", a);
			};
			AddWorld(RavEngine::New<ClientMenu>());

			Debug::Log("Started client on {}", PORT);
		}

		SetWindowTitle(std::format("{} {} | {}", APPNAME, networkManager.IsServer()? "Server" : "Client", GetRenderEngine().GetCurrentBackendName()).c_str());
	}
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};
START_APP(NetApp)
