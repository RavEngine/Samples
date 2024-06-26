
#include "ravengine_shader.glsl"

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;


#include "sprite_particle_layout.glsl"

#include "utility.glsl"

const float maxLife = 200;

void update(inout ParticleData data, inout float newLife, uint particleID)
{
    data.scale += ubo.fpsScale * 0.005;

    data.pos.y += ubo.fpsScale * 0.1;

    vec2 movevec = vec2(
        rand(vec2(particleID, particleID)) * 2 - 1,
        rand(vec2(particleID * 2, particleID * 2)) * 2 - 1
    );

    float life = maxLife;

    movevec *= 0.02;

    data.pos.x += movevec.x;
    data.pos.z += movevec.y;
    
    newLife += ubo.fpsScale;

    data.animationFrame = uint(remap(newLife,0,life,0,9));

    if (newLife > life){
        // destroy the particle

       newLife = 0;
    }
}