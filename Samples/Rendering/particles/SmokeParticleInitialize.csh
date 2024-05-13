struct ParticleState
{
    uint aliveParticleCount;
    uint freeListCount;
    uint createdThisFrame;
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
    vec4 rotation;
    vec3 pos;
    vec3 scale;
    float age;
};

layout(std430, binding = 2) buffer particleDataSSBO
{
    ParticleData particleData[];
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
    if (gl_GlobalInvocationID.x > particleState[0].createdThisFrame){
        return;
    }

    uint particleID = particlesCreatedThisFrameBuffer[gl_GlobalInvocationID.x];

    ParticleData data;
    data.age = 0;
    data.scale = vec3(0.1,0.1,0.1);
    data.pos = vec3(
        rand(vec2(particleID,particleID)),
        rand(vec2(particleID * 2,particleID * 2)),
        rand(vec2(particleID / 2,particleID / 2))
    );
    data.rotation = vec4(0,0,0,1);

    particleData[particleID] = data;
}