#include "ravengine_shader.glsl"

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;


struct ParticleData{
    vec3 pos;
    vec2 scale;
    uint animationFrame;
};


float rand(in vec2 ip) {
    const float seed = 12345678;
    uvec2 p = uvec2(floatBitsToUint(ip.x), floatBitsToUint(ip.y));
    uint s = floatBitsToUint(seed);
    s ^= (s ^ ((~p.x << s) + (~p.y << s)));
    
    p ^= (p << 17U);
    p ^= ((p ^ s) >> 13U);
    p ^= (p << 5U);
    p ^= ((s + (s&(p.x^p.y))) >> 3U);
    
    uint n = (p.x*s+p.y)+((p.x ^ p.y) << ~p.x ^ s) + ((p.x ^ p.y) << ~p.y ^ s);
    return float(n*50323U) / float(0xFFFFFFFFU);
}

const float maxLife = 20;

void update(inout ParticleData data, inout float newLife, uint particleID)
{
    data.scale += ubo.fpsScale * 0.05;

    data.pos.y += ubo.fpsScale * 0.01;

    vec2 movevec = vec2(
        rand(vec2(particleID, particleID)) * 2 - 1,
        rand(vec2(particleID * 2, particleID * 2)) * 2 - 1
    );

    float life = maxLife;

    movevec *= 0.02;

    data.pos.x += movevec.x;
    data.pos.z += movevec.y;
    
    newLife += ubo.fpsScale;

    data.animationFrame = uint(remap(newLife,0,life,0,11));

    if (newLife > life){
        // destroy the particle

       newLife = 0;
    }
}