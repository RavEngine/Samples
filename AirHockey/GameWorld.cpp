#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/InputManager.hpp>
#include <fmt/format.h>
#include "MainMenu.hpp"
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioRoom.hpp>

Ref<PBRMaterialInstance> Puck::material;
using namespace std;

Tween<decimalType,decimalType> t;

GameWorld::GameWorld(int numplayers) : numplayers(numplayers){}

void GameWorld::OnActivate(){
	Ref<Entity> cameraActor = make_shared<Entity>();
	cameraActor->EmplaceComponent<CameraComponent>()->setActive(true);
	cameraActor->EmplaceComponent<AudioListener>();
	cameraBoom->transform()->SetWorldPosition(vector3(0,0,0));
	
	cameraBoom->transform()->AddChild(cameraActor->transform());
	cameraActor->transform()->LocalTranslateDelta(vector3(0,3,3));
	cameraActor->transform()->LocalRotateDelta(vector3(glm::radians(-90.0),0,0));
	
	Spawn(cameraActor);
	Spawn(cameraBoom);
	Spawn(hockeytable);
	
	//create the puck
	puck->transform()->LocalTranslateDelta(vector3(0,3,0));
	Spawn(puck);
	
	InitPhysics();
	
	//intro animation
	t = Tween<decimalType,decimalType>([=](decimalType d, decimalType p){
		cameraBoom->transform()->SetLocalRotation(vector3(glm::radians(d),glm::radians(90.0),0));
		cameraActor->transform()->SetLocalPosition(vector3(0,p,0));
	},90,15);
	t.AddKeyframe(3, TweenCurves::QuinticInOutCurve,0,7);
	
	Ref<Entity> lightmain = make_shared<Entity>();
	auto key = lightmain->EmplaceComponent<DirectionalLight>();
	key->Intensity = 1;
	key->color = {1,0.6,0.404,1};
	auto fill = lightmain->EmplaceComponent<AmbientLight>();
	fill->Intensity=0.4;
	fill->color = {0,0,1,1};
	lightmain->transform()->LocalRotateDelta(vector3(glm::radians(45.0),0,glm::radians(-45.0)));
	auto room = lightmain->EmplaceComponent<AudioRoom>();
	room->SetRoomDimensions(vector3(30,30,30));
	room->WallMaterials()[0] = RoomMat::kMarble;
	
	Spawn(lightmain);
	
	//inputs
	Ref<InputManager> is = make_shared<InputManager>();
	is->AddAxisMap("P1MoveUD", SDL_SCANCODE_W,-1);
	is->AddAxisMap("P1MoveUD", SDL_SCANCODE_S);
	is->AddAxisMap("P1MoveLR", SDL_SCANCODE_D,-1);
	is->AddAxisMap("P1MoveLR", SDL_SCANCODE_A);
	
	is->AddAxisMap("P2MoveUD", SDL_SCANCODE_UP,-1);
	is->AddAxisMap("P2MoveUD", SDL_SCANCODE_DOWN);
	is->AddAxisMap("P2MoveLR", SDL_SCANCODE_RIGHT,-1);
	is->AddAxisMap("P2MoveLR", SDL_SCANCODE_LEFT);
	
	p1 = make_shared<Paddle>(ColorRGBA{1,0,0,1});
	auto p1s = p1->EmplaceComponent<Player>();
	
	p2 = make_shared<Paddle>(ColorRGBA{0,1,0,1});
	auto p2s = p2->EmplaceComponent<Player>();
	
	switch(numplayers){
		case 2:
			is->BindAxis("P2MoveUD", p2s, &Player::MoveUpDown, CID::ANY);
			is->BindAxis("P2MoveLR", p2s, &Player::MoveLeftRight, CID::ANY);
			break;
		case 0:
			//set p1 as a bot
			p1->EmplaceComponent<BotPlayer>(p1s, true);
			// no break here, want to create a bot for p2 in either case
		case 1:
			//create a bot player
			p2->EmplaceComponent<BotPlayer>(p2s, false);
			break;
		default:
			Debug::Fatal("Invalid number of players: {}", numplayers);
	}
	
	if (numplayers > 0){
		//bind inputs
		is->BindAxis("P1MoveUD", p1s, &Player::MoveUpDown, CID::ANY);
		is->BindAxis("P1MoveLR", p1s, &Player::MoveLeftRight, CID::ANY);
	}
	
	Spawn(p1);
	Spawn(p2);
	
	
	Ref<Entity> gamegui = make_shared<Entity>();
	auto context = gamegui->EmplaceComponent<GUIComponent>();
	auto doc = context->AddDocument("demo.rml");
	Scoreboard = doc->GetElementById("scoreboard");
	Spawn(gamegui);
	
	App::inputManager = is;
	
	Reset();
}

void GameWorld::posttick(float f)
{
	t.step(f);
	
	//if the puck's z position > 6 then the right side must have scored
	auto pos = puck->transform()->GetWorldPosition();
	if (pos.z > 6){
		p2score++;
		Reset();
	}
	else if (pos.z < -6){
		p1score++;
		Reset();
	}
}

void GameWorld::Reset(){
	puck->transform()->SetWorldPosition(vector3(0,2,0));
	p1->transform()->SetWorldPosition(vector3(2,2,3));
	p2->transform()->SetWorldPosition(vector3(-2,2,-3));

	//clear velocities
	auto zerovel = [](Ref<Entity> e){
		e->GetComponent<RigidBodyDynamicComponent>()->SetLinearVelocity(vector3(0,0,0), false);
	};
	
	zerovel(p1);
	zerovel(p2);
	zerovel(puck);
	Scoreboard->SetInnerRML(fmt::format("Score: {} - {}", p1score, p2score).c_str());
	
	if (p1score >= numToWin){
		Scoreboard->SetInnerRML("Player 1 Wins!");
		GameOver();
	}
	else if (p2score >= numToWin){
		Scoreboard->SetInnerRML("Player 2 Wins!");
		GameOver();
	}
}

void GameWorld::GameOver(){
	
	Ref<Entity> gameOverMenu = make_shared<Entity>();
	auto ctx = gameOverMenu->EmplaceComponent<GUIComponent>();
	auto doc = ctx->AddDocument("gameover.rml");
	
	struct MenuEventListener: public Rml::EventListener{
		WeakRef<GameWorld> gm;
		MenuEventListener(WeakRef<GameWorld> w) : gm(w){}
		void ProcessEvent(Rml::Event& event) override{
			App::DispatchMainThread([=]{
				auto world = make_shared<MainMenu>();
				App::AddWorld(world);
				App::SetRenderedWorld(world);
				App::RemoveWorld(gm.lock());
			});
		}
	};
	struct ReplayEventListener: public Rml::EventListener{
		WeakRef<GameWorld> gm;
		ReplayEventListener(WeakRef<GameWorld>g) : gm(g){}
		bool isLoading = false;
		void ProcessEvent(Rml::Event& event) override{
			if (!isLoading){
				isLoading = true;
				App::DispatchMainThread([=]{
					auto world = make_shared<GameWorld>(gm.lock()->numplayers);
					App::AddWorld(world);
					App::SetRenderedWorld(world);
					App::RemoveWorld(gm.lock());
				});
			}
		}
	};
	doc->GetElementById("mainmenu")->AddEventListener("click", new MenuEventListener(static_pointer_cast<GameWorld>(shared_from_this())));
	doc->GetElementById("replay")->AddEventListener("click", new ReplayEventListener(static_pointer_cast<GameWorld>(shared_from_this())));
	
	//create a new input manager to stop game inputs and enable UI inputs
	Ref<InputManager> im = make_shared<InputManager>();
	
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
	im->BindAxis("MouseX", ctx, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", ctx, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(ctx);
	
	App::inputManager = im;

	Spawn(gameOverMenu);
}

GameWorld::GameWorld(const GameWorld& other) : GameWorld(other.numplayers){}
