#include "AsteroidShared.glsl"

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;


void update(inout ParticleData data, inout float newLife, uint particleID)
{    
    newLife += ubo.fpsScale;

    if (newLife > 300)
    {
        // destroy the particle

        newLife = 0;
    }
}