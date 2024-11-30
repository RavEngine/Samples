#include "SceneLoader.hpp"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <RavEngine/Debug.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/Filesystem.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/VirtualFileSystem.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/ImportLib.hpp>

using namespace RavEngine;
using namespace std;

constexpr static auto aiflags = aiProcess_CalcTangentSpace |
aiProcess_GenSmoothNormals |
aiProcess_JoinIdenticalVertices |
aiProcess_ImproveCacheLocality |
aiProcess_LimitBoneWeights |
aiProcess_RemoveRedundantMaterials |
aiProcess_SplitLargeMeshes |
aiProcess_Triangulate |
aiProcess_GenUVCoords |
aiProcess_SortByPType |
//aiProcess_FindDegenerates               |
aiProcess_FindInstances |
aiProcess_ValidateDataStructure |
aiProcess_OptimizeMeshes |
aiProcess_FindInvalidData;

SceneLoader::SceneLoader(const std::string& name) : SceneLoader(name.c_str()){}

RavEngine::SceneLoader::SceneLoader(const char* name) : scene_path(name)
{
	auto dir = Format("objects/{}",name);

	if (!GetApp()->GetResources().Exists(dir.c_str())) {
		Debug::Fatal("Cannot open resource: {}", dir);
	}

	auto str = GetApp()->GetResources().FileContentsAt(dir.c_str());

	auto file_ext = Filesystem::Path(dir).extension();
	//uses a meta-flag to auto-triangulate the input file
	scene = aiImportFileFromMemory(reinterpret_cast<char*>(str.data()), Debug::AssertSize<unsigned int>(str.size()),aiflags,file_ext.string().c_str());

	if (!scene) {
		Debug::Fatal("Cannot load: {}", aiGetErrorString());
	}
}

SceneLoader::SceneLoader(const Filesystem::Path& path) : scene_path(path.string()) {
	scene = aiImportFile(path.string().c_str(), aiflags);
	
	if (!scene) {
		Debug::Fatal("Cannot load: {}", aiGetErrorString());
	}
}

RavEngine::SceneLoader::~SceneLoader()
{
	aiReleaseImport(scene);
}

void RavEngine::SceneLoader::LoadObjects(const Function<void(const ImportedObject&)>& func)
{
	auto getWorldMatrix = [](const aiNode * node) -> aiMatrix4x4 {
		// figure out size
		uint16_t depth = 0;
		for (aiNode* p = node->mParent; p != nullptr; p = p->mParent) {
			++depth;
		}
		stackarray(transforms, aiMatrix4x4, depth);

		uint16_t tmp = 0;
		for (aiNode* p = node->mParent; p != nullptr; p = p->mParent) {
			transforms[tmp] = p->mTransformation;
			++tmp;
		}

		aiMatrix4x4 mat;	//identity
		if (depth > 0) {
			for (int i = depth - 1; i >= 0; --i) {
				mat *= transforms[i];
			}
		}
		mat *= node->mTransformation;
		return mat;
	};

	UnorderedMap<uint32_t, Ref<PBRMaterialInstance>> materials;	 // not an array because they can be encountered out of order
	const Filesystem::Path base_path = decltype(base_path)(scene_path).parent_path();
	auto recurse_node = [&](aiNode* node) -> void {
		auto recurse_node_impl = [&](aiNode* node, auto& recursive_func) -> void {
			// process the node
			aiVector3t<float> scale, position;
			aiQuaterniont<float> rotation;
			getWorldMatrix(node).Decompose(scale, rotation, position);
			ImportedObject l;
			l.name = std::string_view(node->mName.C_Str(), node->mName.length);
			l.translate = vector3(position.x, position.y, position.z);
			l.scale = vector3(scale.x, scale.y, scale.z);
			l.rotation = quaternion(rotation.w, rotation.x, rotation.y, rotation.z);

			// get the meshes
			for (uint32_t i = 0; i < node->mNumMeshes; i++) {
				constexpr matrix4 identity(1);

				const auto mesh = scene->mMeshes[node->mMeshes[i]];
				try {
					auto mp = AIMesh2MeshPart(mesh, identity);
					auto asset = New<MeshAsset>(std::move(mp));
					// load the material data
					auto idx = mesh->mMaterialIndex;
					Ref<PBRMaterialInstance> matinst;
					if (materials.contains(idx)) {
						matinst = materials.at(idx);
					}
					else {
						// create the material here
						matinst = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
						materials[idx] = matinst;
						auto aimat = scene->mMaterials[idx];
						aiColor3D albedo;
						aimat->Get(AI_MATKEY_COLOR_DIFFUSE, albedo);
						matinst->SetAlbedoColor({ albedo.r,albedo.g,albedo.b,1 });

						// load textures
						aiString texpath;
						if (aimat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texpath) == AI_SUCCESS) {
							auto imgpath = Filesystem::Path(Format("{}/{}", base_path.string(), texpath.C_Str()));
							auto tx = New<Texture>(imgpath);
							matinst->SetAlbedoTexture(tx);
						}

					}

					Debug::Assert(asset != nullptr, "mesh is null!");
					Debug::Assert(matinst != nullptr, "material is null!");

					l.material = matinst;
					l.mesh = asset;

					func(l);
				}
				catch (const std::exception& e) {
					Debug::Warning("Skipping {} due to error {}", l.name, e.what());
				}
			}

			for ( decltype(node->mNumChildren) i = 0; i < node->mNumChildren; i++) {
				recursive_func(node->mChildren[i], recursive_func);
			}
		};
		recurse_node_impl(node, recurse_node_impl);
	};
	recurse_node(scene->mRootNode);
}
