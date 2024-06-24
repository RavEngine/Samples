#include "AsteroidShared.glsl"

ParticleData init(ParticleInitData initData)
{
    uint particleID = initData.particleID;

    ParticleData data;
   
    data.velocity = vec3(0,0.2,0.2);
    data.rot = vec4(0,0,0,1);
    data.scale = vec3(1,1,1);
    data.pos = (initData.emitterModel * vec4(0, 0, 0, 1)).xyz;
    
    return data;
}