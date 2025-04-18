#include "AsteroidShared.glsl"
#include "RavEngine/quat.glsl"

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;

const float kGraivty = 0.5 / 60;
const float scaleDelta = 0.005;

#include "utility.glsl"

void update(inout ParticleData data, inout float newLife, uint particleID)
{    
    newLife += ubo.fpsScale;

    data.velocity.y -= kGraivty * ubo.fpsScale;

    data.scale -= scaleDelta * ubo.fpsScale;

    data.pos += data.velocity; 
    data.rot = quatAdd(data.rot, eulerToQuat(degToRad(vec3(1,1,1) * ubo.fpsScale))) ;

    if (data.pos.y < data.scale.y){
        data.velocity.y = abs(data.velocity.y);
    }

    if (newLife > 250){
        data.alpha = remap(newLife, 250, 300, 1, 0);
    }

    if (newLife > 300)
    {
        // destroy the particle

        newLife = 0;
    }
}