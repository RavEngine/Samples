#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>
#include <SDL3/SDL_dialog.h>
#include <RavEngine/Window.hpp>

using namespace RavEngine;
using namespace std;



struct TextureViewerWorld : public RavEngine::World {	
 
	Ref<PBRMaterialInstance> mat;
	ComponentHandle<Transform> planeTransform;
	TextureViewerWorld() {
		
		auto cubeEntity = Instantiate<GameObject>();

		mat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		auto mesh = MeshCollectionStaticManager::Get("quad");
		cubeEntity.EmplaceComponent<StaticMesh>(mesh, mat);
		cubeEntity.GetTransform().LocalRotateDelta(vector3{deg_to_rad(90),0.f,0.f});
		planeTransform = cubeEntity;

		auto cameraEntity = Instantiate<GameObject>();

		auto& cameraComponent = cameraEntity.EmplaceComponent<CameraComponent>();

		cameraComponent.SetActive(true);

		cubeEntity.GetTransform().LocalTranslateDelta(vector3(0, 0, -5));

		auto lightsEntity = Instantiate<GameObject>();
		lightsEntity.EmplaceComponent<DirectionalLight>().SetIntensity(4);
		lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);

		lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });
	}

	void LoadTexture(const Filesystem::Path& path) {
		auto tx = New<Texture>(path);
		mat->SetAlbedoTexture(tx);
		auto dim = tx->GetTextureSize();;
		auto aspect = (float)dim.width / dim.height;
		planeTransform->SetLocalScale({ aspect,1,1 });
	}
};

struct TextureViewerApp : public RavEngine::App {
	constexpr static SDL_DialogFileFilter filters[] = { {"Any file", "*"} };

	Ref<TextureViewerWorld> world;

	void OnStartup(int argc, char** argv) final {

		SetWindowTitle("TextureViewer");

		world = RavEngine::New<TextureViewerWorld>();

		AddWorld(world);
		LoadNewTexture();
	}

	void OnFatal(const std::string_view msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
	}

	void LoadNewTexture() {
		SDL_ShowOpenFileDialog([](void* userdata, const char* const* filelist, int filter) {

			auto app = static_cast<TextureViewerApp*>(userdata);
			if (filelist == nullptr) {
				Debug::Fatal("An error occured: {}", SDL_GetError());
				app->Quit();
			}
			if (filelist && *filelist) {
				Filesystem::Path chosenFile(*filelist);
				app->DispatchMainThread([app,chosenFile] {
					app->world->LoadTexture(chosenFile);
				});
			}
			else {
				app->Quit();
			}


			}, this, GetMainWindow()->window, filters, std::size(filters), NULL, false);
	}
};

START_APP(TextureViewerApp)