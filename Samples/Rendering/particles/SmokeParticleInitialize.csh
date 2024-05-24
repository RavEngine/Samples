#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct ParticleState
{
    uint aliveParticleCount;
    uint freeListCount;
    uint createdThisFrame;
    uint emitterOwnerID;
};

layout(std430, binding = 0) readonly buffer particleStateSSBO
{   
    ParticleState particleState[];
};

layout(std430, binding = 1) readonly buffer createdThisFrameSSBO
{
    uint particlesCreatedThisFrameBuffer[];
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

layout(std430, binding = 4) readonly buffer modelMatrixBuffer{
    mat4 model[];
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
    if (gl_GlobalInvocationID.x >= particleState[0].createdThisFrame){
        return;
    }

    uint particleID = particlesCreatedThisFrameBuffer[gl_GlobalInvocationID.x];

    ParticleData data;
    
    data.scale = vec2(0.1,0.1);
    vec4 pos = vec4(
        rand(vec2(particleID,particleID)),
        rand(vec2(particleID * 2,particleID * 2)),
        rand(vec2(particleID / 2,particleID / 2)),
        1
    );

    mat4 emitterModel = model[particleState[0].emitterOwnerID];

    pos = emitterModel * pos;

    data.pos = pos.xyz;

    data.animationFrame = 0;

    particleData[particleID] = data;

    particleLifeBuffer[particleID] = 1.0;
}