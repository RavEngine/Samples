#include "CameraEntity.hpp"
#include <RavEngine/CameraComponent.hpp>

using namespace RavEngine;
using namespace std;

CameraEntity::CameraEntity(Ref<Character> cm) : target(cm){
	EmplaceComponent<CameraComponent>()->setActive(true);
}

void CameraEntity::MoveForward(float amt){
}

void CameraEntity::MoveRight(float amt){
}
