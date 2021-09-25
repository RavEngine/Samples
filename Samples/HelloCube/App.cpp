#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>

using namespace RavEngine;
using namespace std;

// Start by defining an application class that derives from RavEngine::App.
struct HelloCubeApp : public RavEngine::App {

	// Implement a constructor that calls this superclass constructor. The parameter
	// passed here is the name of the resources zip file that your application is loading.
	// when using pack_resources in CMake, supply here the name of your target.
	HelloCubeApp() : App(APPNAME) {}

	// Next, implement OnStartup. This is called when your application launches.
	// You are passed argc and argv from the command line. 
	void OnStartup(int argc, char** argv) final;
};

// After defining an App, define a World by creating a class that derives from RavEngine::World.
// A world is akin to a Scene in Unity or a Level in Unreal. Worlds contain all the action in a game.
struct HelloCubeWorld : public RavEngine::World {

	// Implement OnActivate. The engine invokes this method automatically when an instance of this
	// world has become Active. Active worlds are connected to the render engine. RavEngine can have multiple
	// worlds loaded and running at once, but only one Active world. Do not worry about this yet. 
	void OnActivate() final {

		// We can do basic world construction in this method for the convenience of this tutorial. 
		// If this world will be loaded and unloaded, do not do initialization in this method as
		// each time the world is made active, code here runs.

		// Create an Entity. Entities are akin to GameObjects in Unity.
		// Many RavEngine features leverage reference counting, so use std::make_shared to construct them.
		auto cubeEntity = make_shared<Entity>();

		// We want to display a cube in this world. RavEngine uses a component-based composition model 
		// for describing scene objects. However, you can also subclass RavEngine::Entity and perform
		// setup inside its constructor for Unreal-style inheritance. 

		// We will start by loading the cube mesh. The cube is one of the default primitives that comes with RavEngine.
		auto cubeMesh = MeshAsset::Manager::GetDefault("cube.obj");

		// Next we need to define a material for the cube. We can use the default material.
		// RavEngine can optimize your rendering for you by batching if you minimize the number of Material Instances you create,
		// and share them wherever possible. 
		auto cubeMat = make_shared<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());

		// A StaticMesh defines a fixed (non-deforming) rendered polygon, which is perfect for our cube.
		// Note that all StaticMeshes must have a material bound to them. A StaticMesh without a material will cause
		// the engine to crash, as that is an invalid state.
		// The EmplaceComponent method constructs the component inline and attaches it to the entity.
		cubeEntity->EmplaceComponent<StaticMesh>(cubeMesh, cubeMat);

		// Now that we have our cube, let's place it in the world.
		Spawn(cubeEntity);

		// We want to be able to see our cube, so we need a camera. In RavEngine, cameras are also components, so 
		// we need another entity to hold that. 
		auto cameraEntity = make_shared<Entity>();

		// Create the CameraComponent. The EmplaceComponent call returns an owning pointer to the constructed component.
		// Be wary of storing these to avoid reference cycles that lead to memory leaks. 
		auto cameraComponent = cameraEntity->EmplaceComponent<CameraComponent>();

		// By default, cameras are disabled, and do not render. We must enable our camera for it to display anything in the world.
		cameraComponent->SetActive(true);

		// Add the camera to the world.
		Spawn(cameraEntity);

		// As of this line, the camera is inside the cube. To rectify this, let's place the cube in front of the camera.
		cubeEntity->GetTransform()->LocalTranslateDelta(vector3(0,0,-5));

		// We want some lighting on our cube. In RavEngine, lights are also components, so we'll need an entity for those.
		auto lightsEntity = make_shared<Entity>();
		lightsEntity->EmplaceComponent<DirectionalLight>();					// a light that mimics the sun
		lightsEntity->EmplaceComponent<AmbientLight>()->Intensity = 0.2;	// a weak fill light that affects all surfaces equally

		// Lights use the transformation of their parent entity to determine their rotation and position.
		lightsEntity->GetTransform()->LocalRotateDelta(vector3{ glm::radians(45.0),glm::radians(45.0),0 });

		// add the lights to the world
		Spawn(lightsEntity);
	}

	// The engine calls it synchronously every tick after the rest of the pipeline has finished processing.
	void PostTick(float tickrateScale) final {

		// We can hold onto an entity as a class variable, but I'll instead use this opportunity to demonstrate the query system.
		// RavEngine worlds can be queried extremely efficiently by component type. Since we know that this world contains
		// one static mesh, we can use that to get our entity.
		auto meshCompOpt = GetComponent<StaticMesh>();

		// however, that call gives us a component pointer optional. Components store their owners as weak pointers, so we can use
		// GetOwner to get the owner.
		if (meshCompOpt) {
			auto meshComp = meshCompOpt.value();
			auto entity = meshComp->GetOwner().lock();	//convert to strong pointer

			// Let's spin our cube.
			// RavEngine expects rotations in radians. Use glm::radians to convert to degrees.
			auto rotVec = vector3(glm::radians(1.0), glm::radians(2.0), glm::radians(-0.5));	

			// Unlike most engines, RavEngine's render engine is asynchronous. This means that the engine 'ticks'
			// at a different rate that it renders frames. One tick =/= one frame. In addition, if the engine were to fall behind, 
			// we need to ensure our game does not run in slow motion. To accomplish this, we simply multiply our movements by 
			// a scale factor passed into this method. RavEngine has already calcuated the scale factor for us. This is *not* a deltaTime,
			// like in Unity.
			rotVec *= tickrateScale;

			// Entities can also be queried efficiently for components, just like worlds. Since Transforms are 
			// a very frequent access, Entities provide the convenience function GetTransform, to use instead.
			entity->GetComponent<Transform>().value()->LocalRotateDelta(rotVec);
		}
	}
};

// We've defined a world, but now we need to load it. OnStartup is a good place to load your initial world.
void HelloCubeApp::OnStartup(int argc, char** argv) {

	// make an instance of the world
	auto level = make_shared<HelloCubeWorld>();

	// Tell the engine to switch to this world.
	// If the engine has no worlds active, it will automatically set the first one as the active world.
	AddWorld(level);
}

// Last thing - we need to launch our application. RavEngine supplies a convenience macro for this,
// which simply inlines a main function that launches your app and invokes its OnStartup method.
// You do not need to use this macro if you don't want to.
START_APP(HelloCubeApp)
