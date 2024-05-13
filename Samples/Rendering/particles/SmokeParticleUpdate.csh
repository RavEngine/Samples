layout(push_constant, std430) uniform UniformBufferObject{
    float fpsScale;
} ubo;

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

layout(std430, binding = 1) readonly buffer aliveSSBO
{
    uint aliveParticleIndexBuffer[];
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

    if (data.age > 500){
        // KillParticle();  //TODO: implement
    }

    particleData[particleID] = data;
}