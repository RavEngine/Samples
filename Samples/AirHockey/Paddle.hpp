#pragma once

#include <RavEngine/GameObject.hpp>


class Paddle : public RavEngine::GameObject{
public:
	void Create(const RavEngine::ColorRGBA& color);
};
