#pragma once
#include <RavEngine/Function.hpp>
#include <RavEngine/Ref.hpp>
#include <RavEngine/mathtypes.hpp>
#include <RavEngine/Filesystem.hpp>

struct aiScene;

namespace RavEngine {
	class Entity;
	class MeshAsset;
	class PBRMaterialInstance;

	struct PreloadedAsset {
		std::string_view name;
	};

	struct PreloadedLight : public PreloadedAsset {
		// light details here...
	};
 
	struct ImportedObject : public PreloadedAsset {
		vector3 translate, scale;
		quaternion rotation;
		Ref<MeshAsset> mesh;
		Ref<PBRMaterialInstance> material;
	};

	struct SceneLoader{

        /**
        * Construct a SceneLoader. This will load the scene file into an intermediate representation.
        */
        SceneLoader(const char* sceneFile);
		/**
		* Construct a SceneLoader. This will load the scene file into an intermediate representation.
		*/
		SceneLoader(const std::string& sceneFile);
		
		/**
		 Construct a SceneLoader from the user's filesystem. This will load the scene file into an intermediate representation
		 */
        SceneLoader(const Filesystem::Path& pathOnDisk);

		/**
		* Unloads internal representation
		*/
		~SceneLoader();
		/**
		* Load the scene nodes for this scene
		* @param func the function to invoke with each node
		*/
		void LoadObjects(const Function<void(const ImportedObject&)>& func);

	private:
		const aiScene* scene;
		const std::string scene_path;
	};


}
