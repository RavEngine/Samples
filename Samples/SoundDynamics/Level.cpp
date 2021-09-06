#include "Level.hpp"
#include "Player.hpp"
#include "Speaker.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/AudioRoom.hpp>
#include <filesystem>

using namespace RavEngine;
using namespace std;

struct InputNames {
	static constexpr char const
		* MoveForward = "MoveForward",
		* MoveRight = "MoveRight",
		* MoveUp = "MoveUp",
		* LookRight = "LookRight",
		* LookUp = "LookUp";
};

void Level::OnActivate() {
	// lights
	auto lightEntity = make_shared<Entity>();
	lightEntity->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	lightEntity->EmplaceComponent<DirectionalLight>();
	lightEntity->GetTransform()->LocalRotateDelta(vector3{glm::radians(35.0),glm::radians(-30.0),0});
	Spawn(lightEntity);

	// create the audio room
	auto stage = make_shared<Stage>();
	Spawn(stage);

	// create player 
	auto player = make_shared<Player>();
	Spawn(player);
	player->GetTransform()->SetLocalRotation(vector3(0, glm::radians(-90.f), 0));
	player->GetTransform()->SetLocalPosition(vector3(-5,2,0));

	// load UI
	auto uiEntity = make_shared<Entity>();
	auto ui = uiEntity->EmplaceComponent<GUIComponent>();
	auto doc = ui->AddDocument("main.rml");
	Spawn(uiEntity);

	std::array<std::string, RoomMat::kNumMaterialNames> names{
		"Transparent",
		"Acoustic Ceiling Tiles",
		"Bare Brick",
		"Painted Brick",
		"Coarse Concrete Block",
		"Painted Concrete Block",
		"Heavy Curtain",
		"Fiberglass Insulation",
		"Thin Glass",
		"Thick Glass",
		"Grass",
		"Linoleum On Concrete",
		"Marble",
		"Metal",
		"Parquet On Concrete",
		"Rough Plaster",
		"Smooth Plaster",
		"Plywood Panel",
		"Polished Concrete or Tile",
		"Sheetrock",
		"Water or Ice Surface",
		"Wood Panel",
		"Uniform"
	};

	wallTextures[0] = TextureManager::defaultTexture;
	wallTextures[23] = TextureManager::defaultTexture;
	App::Resources->IterateDirectory("textures", [&](const string& file) {
		auto name = std::filesystem::path(file).filename();
		auto tex = make_shared<Texture>(name.string());
		auto pos = std::distance(names.begin(), std::find(names.begin(), names.end(), name.replace_extension("").string()));

		if (pos != 24) {
			wallTextures[pos] = tex;
		}
		else {
			Debug::Warning("Skipped texture {}", file);
		}

	});

	for (int i = 0; i < 6; i++) {
		auto sel = doc->CreateElement("select");
		
		for (int j = 0; j < RoomMat::kNumMaterialNames; j++) {
			auto opt = doc->CreateElement("option");
			if (j == 0) {
				opt->SetAttribute("selected", true);
			}
            opt->SetAttribute("value", StrFormat("{}",j));
			opt->SetInnerRML(names[j]);
			sel->AppendChild(std::move(opt));
		}

		// change event listener
		struct WallMaterialChangeEventListener : public Rml::EventListener {
			uint8 roomFace;
			Ref<AudioRoom> room;
			Ref<Stage> stage;
			WallMaterialChangeEventListener(decltype(roomFace) rf, decltype(room) room, decltype(stage) stage) : stage(stage), roomFace(rf), room(room){}

			void ProcessEvent(Rml::Event& evt) final {
				auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
				room->WallMaterials()[roomFace] = static_cast<RoomMat>(selbox->GetSelection());
				auto owner = room->GetOwner().lock();
				auto world = static_pointer_cast<Level>(owner->GetWorld().lock());
				auto material = stage->wallMaterials[roomFace];
				auto tex = world->wallTextures[selbox->GetSelection()];
				material->SetAlbedoTexture(tex);
			}
		};

		sel->AddEventListener(Rml::EventId::Change, new WallMaterialChangeEventListener(i,stage->GetRoom(),stage));

		doc->GetElementById("materials")->AppendChild(std::move(sel));
	}

	struct MusicChangeEventListener : public Rml::EventListener {
		WeakRef<Level> world;

		MusicChangeEventListener(decltype(world) world) : world(world) {}

		void ProcessEvent(Rml::Event& evt) final {
			if (auto owning = world.lock()) {
				auto sources = owning->GetAllComponentsOfType<AudioSourceComponent>();
				auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
				for (const auto& source : sources) {
					auto player = static_pointer_cast<AudioSourceComponent>(source);
					player->SetAudio(owning->tracks[selbox->GetSelection()]);
					player->Restart();
				}
			}
		}
	};
	auto musicsel = doc->GetElementById("music");
	musicsel->AddEventListener(Rml::EventId::Change, new MusicChangeEventListener(static_pointer_cast<Level>(shared_from_this())));
	
	// load audio & initialize music selector
    {
        int music_id = 0;
        App::Resources->IterateDirectory("sounds", [&](const string& track) {
            auto path = std::filesystem::path(track);
            if (path.extension() == ".mp3") {
                auto leaf_name = path.filename();
                tracks.push_back(make_shared<AudioAsset>(leaf_name.string()));
                auto opt = doc->CreateElement("option");
                opt->SetAttribute("value", StrFormat("{}",music_id++));     // when creating options, we must assign them a value, otherwise the change event on the selector doesn't trigger if the option is selected
                opt->SetInnerRML(leaf_name.string());
                musicsel->AppendChild(std::move(opt));
            }
        });
    }

	// auto select first
	auto firstopt = musicsel->QuerySelector("option");
	firstopt->SetAttribute("selected", true);

	// create speakers
	auto speaker1 = make_shared<Speaker>(tracks[0]);
	speaker1->GetTransform()->LocalTranslateDelta(vector3(5, 0, -2));
	Spawn(speaker1);

	auto speaker2 = make_shared<Speaker>(tracks[0]);
	speaker2->GetTransform()->LocalTranslateDelta(vector3(5, 0, 2));
	Spawn(speaker2);

	// setup inputs
	auto im = App::inputManager = make_shared<InputManager>();
	
	im->AddAxisMap(InputNames::MoveForward, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap(InputNames::MoveRight, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);

	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S,-1);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A, -1);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_SPACE);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT, -1);

	im->AddAxisMap(InputNames::LookRight,Special::MOUSEMOVE_XVEL,-1);
	im->AddAxisMap(InputNames::LookUp,Special::MOUSEMOVE_YVEL,-1);

	im->BindAxis(InputNames::MoveForward, player, &Player::MoveForward, CID::ANY);
	im->BindAxis(InputNames::MoveRight, player, &Player::MoveRight, CID::ANY);
	im->BindAxis(InputNames::MoveUp, player, &Player::MoveUp, CID::ANY);
	im->BindAxis(InputNames::LookRight, player, &Player::LookRight, CID::ANY);
	im->BindAxis(InputNames::LookUp, player, &Player::LookUp, CID::ANY);

	// for gui
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", ui, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", ui, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(ui);

	// initialize physics
	InitPhysics();
}

Level::Level() {

}
