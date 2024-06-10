#include "Level.hpp"
#include "Player.hpp"
#include "Speaker.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/Filesystem.hpp>
#include <RavEngine/AudioGraphAsset.hpp>
#include <RavEngine/VirtualFileSystem.hpp>
#include <RavEngine/Texture.hpp>
#include "AudioMIDI.hpp"
#include "AudioExporter.hpp"

using namespace RavEngine;
using namespace std;

struct InputNames {
	static constexpr char const
		* MoveForward = "MoveForward",
		* MoveRight = "MoveRight",
		* MoveUp = "MoveUp",
		* LookRight = "LookRight",
		* LookUp = "LookUp",
        * ToggleMouse = "ToggleMouse"
        ;
};

void Level::ToggleMouse(){
	GetApp()->inputManager->SetRelativeMouseMode(!GetApp()->inputManager->GetRelativeMouseMode());
}

Level::Level(){
	// lights
	auto lightEntity = Instantiate<GameObject>();
	lightEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
	lightEntity.EmplaceComponent<DirectionalLight>().SetCastsShadows(true);
	lightEntity.GetTransform().LocalRotateDelta(vector3{deg_to_rad(35),deg_to_rad(-30),0});

	// create the audio room
	auto stage = Instantiate<Stage>();

	// create player 
	auto player = Instantiate<Player>();
	player.GetTransform().SetLocalRotation(vector3(0, deg_to_rad(-90), 0)).SetLocalPosition(vector3(-5,2,0));

	// load UI
	auto uiEntity = Instantiate<Entity>();
	auto& ui = uiEntity.EmplaceComponent<GUIComponent>();
	auto doc = ui.AddDocument("main.rml");


	struct MusicChangeEventListener : public Rml::EventListener {
		Level* world;

		MusicChangeEventListener(decltype(world) world) : world(world) {}

        void ProcessEvent(Rml::Event& evt) final {
            auto sources = world->GetAllComponentsOfType<AudioSourceComponent>();
            
            auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
            auto songName = selbox->GetOption(selbox->GetSelection())->GetInnerRML();
            auto player = world->tracks.contains(songName) ? world->tracks.at(songName) : nullptr;
            if (player){
                player->Restart();
                player->Play();  // if the song reaches the end, it will automatically stop, so we need to re-play.
                for(auto& source : *sources){
                    source.SetPlayer(player);
                }
            }
            else{
                Debug::Fatal("No loaded song {}",songName);
            }
           
		}
	};
	auto musicsel = doc->GetElementById("music");
	musicsel->AddEventListener(Rml::EventId::Change, new MusicChangeEventListener(this));
	
	// load audio & initialize music selector
    {
        int music_id = 0;
		GetApp()->GetResources().IterateDirectory("sounds", [&](const string& track) {
           
            
            auto createElement = [&music_id,doc,musicsel](const std::string& name){
                auto opt = doc->CreateElement("option");
                opt->SetAttribute("value", Format("{}",music_id++));     // when creating options, we must assign them a value, otherwise the change event on the selector doesn't trigger if the option is selected
                opt->SetInnerRML(name);
                musicsel->AppendChild(std::move(opt));
            };
            // mono effect graph
            auto effectGraph = New<AudioGraphAsset>(1);
            effectGraph->filters.emplace_back(New<AudioGainFilterLayer>(0.5f));
            
            auto path = Filesystem::Path(track);
            if (path.extension() == ".mp3") {
                auto leaf_name = path.filename();
                auto player = RavEngine::New<SampledAudioDataProvider>(RavEngine::New<AudioAsset>(leaf_name.string()));
                tracks[leaf_name] = player;
                player->SetGraph(effectGraph);
                player->Play();
                createElement(leaf_name.string());
            }
            else if (path.extension() == ".mid"){
#if 0
                auto leaf_name = path.filename();
                auto player = New<AudioMIDIPlayer>();
                auto instrument1 = std::make_shared<InstrumentSynth>("Harp.sfz");
                auto instrument2 = std::make_shared<InstrumentSynth>("Harp.sfz");
                instrument1->setNumVoices(512);
                instrument2->setNumVoices(512);
                instrument1->setVolume(6);
                instrument2->setVolume(6);
                player->SetInstrumentForTrack(0, instrument1);
                player->SetInstrumentForTrack(1, instrument2);
                player->beatsPerMinute = 60;
                
                auto midibytes = GetApp()->GetResources().FileContentsAt<std::vector<uint8_t>>(path.string().c_str());
                Ref<fmidi_smf_t> file{fmidi_smf_mem_read(midibytes.data(), midibytes.size())};
				
				/*AudioMIDIRenderer render;
				auto asset = render.Render(file,*player.get());
				AudioExporter::ExportWavOneShot(asset, "C:/Users/Ravbug/Downloads/output.wav");
                */
                player->SetGraph(effectGraph);
                player->SetMidi(file);
                player->Restart();
                player->Play();
               
                tracks[leaf_name] = player;
                
                createElement(leaf_name.string());
#endif
            }
        });
    }

	// auto select first
	auto firstopt = musicsel->QuerySelector("option");
	firstopt->SetAttribute("selected", true);
    
    auto& firstSong = (*tracks.begin()).second;

	// create speakers
	auto speaker1 = Instantiate<Speaker>(firstSong);
	speaker1.GetTransform().LocalTranslateDelta(vector3(5, 0, -2));

	auto speaker2 = Instantiate<Speaker>(firstSong);
	speaker2.GetTransform().LocalTranslateDelta(vector3(5, 0, 2));

	// setup inputs
	auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
	
	im->AddAxisMap(InputNames::MoveForward, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap(InputNames::MoveRight, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);

	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S,-1);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A, -1);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_SPACE);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT, -1);
    im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

	im->AddAxisMap(InputNames::LookRight,Special::MOUSEMOVE_XVEL,-1);
	im->AddAxisMap(InputNames::LookUp,Special::MOUSEMOVE_YVEL,-1);

    ComponentHandle<PlayerController> pc(player);
	im->BindAxis(InputNames::MoveForward, pc, &PlayerController::MoveForward, CID::ANY);
	im->BindAxis(InputNames::MoveRight, pc, &PlayerController::MoveRight, CID::ANY);
	im->BindAxis(InputNames::MoveUp, pc, &PlayerController::MoveUp, CID::ANY);
	im->BindAxis(InputNames::LookRight, pc, &PlayerController::LookRight, CID::ANY);
	im->BindAxis(InputNames::LookUp, pc, &PlayerController::LookUp, CID::ANY);
    im->BindAction(InputNames::ToggleMouse, GetInput(this), &Level::ToggleMouse, Pressed, CID::ANY);
    
    // default to camera control
    im->SetRelativeMouseMode(true);

	// for gui
    ComponentHandle<GUIComponent> gh(uiEntity);
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(ui.GetData());

	// initialize physics
	InitPhysics();    
}

