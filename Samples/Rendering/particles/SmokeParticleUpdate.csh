#extension GL_EXT_shader_explicit_arithmetic_types : enable

layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;

struct ParticleState
{
    uint aliveParticleCount;
    uint freeListCount;
    uint createdThisFrame;
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
    float age;
};

layout(std430, binding = 2) buffer particleDataSSBO
{
    ParticleData particleData[];
};

layout(std430, binding = 3)buffer freelistSSBO
{
    uint particleFreelist[];
};

layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;
void main()
{
    if (gl_GlobalInvocationID.x >= particleState[0].aliveParticleCount){
        return;
    }

    uint particleID = aliveParticleIndexBuffer[gl_GlobalInvocationID.x];

    ParticleData data = particleData[particleID];

    data.scale += ubo.fpsScale * 0.05;

    data.pos.y += ubo.fpsScale * 0.1;
    
    data.age += ubo.fpsScale;

    data.animationFrame++;

    if (data.age > 300){
        // destroy the particle

        //TODO: turn this into the DestroyParticle() library function
        //TODO: some mechanism to prevent this getting called multiple times

        uint freelistIdx = atomicAdd(particleState[0].freeListCount,1);
        particleFreelist[freelistIdx] = particleID;
        uint prevTotalAlive = atomicAdd(particleState[0].aliveParticleCount,-1) - 1;
        aliveParticleIndexBuffer[gl_GlobalInvocationID.x] = aliveParticleIndexBuffer[prevTotalAlive];
    }

    particleData[particleID] = data;
}