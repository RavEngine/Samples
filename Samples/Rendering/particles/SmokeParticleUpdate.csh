#extension GL_EXT_shader_explicit_arithmetic_types : enable

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;

struct ParticleState
{
    uint aliveParticleCount;
    uint freeListCount;
    uint createdThisFrame;
    uint emitterOwnerID;
};

layout(std430, binding = 0) buffer particleStateSSBO
{   
    ParticleState particleState[];
};

layout(std430, binding = 1) buffer aliveSSBO
{
    uint aliveParticleIndexBuffer[];
};

struct ParticleData{
    vec3 pos;
    vec2 scale;
    uint animationFrame;
};

layout(scalar, binding = 2) buffer particleDataSSBO
{
    ParticleData particleData[];
};


layout(std430, binding = 3) buffer lifeSSBO
{
    float particleLifeBuffer[];
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


layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;
void main()
{
    if (gl_GlobalInvocationID.x >= particleState[0].aliveParticleCount){
        return;
    }

    uint particleID = aliveParticleIndexBuffer[gl_GlobalInvocationID.x];

    ParticleData data = particleData[particleID];

    data.scale += ubo.fpsScale * 0.005;

    data.pos.y += ubo.fpsScale * 0.1;

    data.pos.x += (rand(vec2(particleID, particleID)) * 2 - 1) * 0.1;
    data.pos.z += (rand(vec2(particleID * 2, particleID * 2)) * 2 - 1) * 0.1;
    
    particleLifeBuffer[particleID] += ubo.fpsScale;

    data.animationFrame++;

    if (particleLifeBuffer[particleID] > 300){
        // destroy the particle

        particleLifeBuffer[particleID] = 0;
    }

    particleData[particleID] = data;
}