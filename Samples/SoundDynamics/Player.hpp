#include <RavEngine/GameObject.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/Window.hpp>

struct PlayerController : public RavEngine::ScriptComponent {
    float scaleFactor = 0;
    float movementSpeed = 0.1;
    float rotationSpeed = 0.05;
    RavEngine::ComponentHandle<RavEngine::Transform> childTransform;

    inline decimalType scale(float amt) {
        return amt * scaleFactor * movementSpeed * RavEngine::GetApp()->GetMainWindow()->GetRelativeMouseMode();
    }

    inline void MoveForward(float amt) {
        auto& tr = GetTransform();
        tr.LocalTranslateDelta(tr.Forward() * scale(amt));
    }

    inline void MoveRight(float amt) {
        auto& tr = GetTransform();
        tr.LocalTranslateDelta(tr.Right() * scale(amt));
    }

    inline void MoveUp(float amt) {
        auto& tr = GetTransform();
        tr.LocalTranslateDelta(tr.Up() * scale(amt));
    }

    inline void LookUp(float amt) {
        childTransform->LocalRotateDelta(vector3(deg_to_rad(amt * rotationSpeed * RavEngine::GetApp()->GetMainWindow()->GetRelativeMouseMode()), 0, 0));
    }

    inline void LookRight(float amt) {
        auto& tr = GetTransform();
        tr.LocalRotateDelta(vector3(0, deg_to_rad(amt * rotationSpeed * RavEngine::GetApp()->GetMainWindow()->GetRelativeMouseMode()), 0));
    }

    void Tick(float scale) final {
        scaleFactor = scale;
    }
    PlayerController(RavEngine::Entity owner) : ScriptComponent(owner){}
};
struct Player : public RavEngine::GameObject {
	void Create();
};
