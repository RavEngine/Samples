#include "AsteroidShared.glsl"

ParticleData init(ParticleInitData initData)
{
    uint particleID = initData.particleID;

    ParticleData data;
   
    data.velocity = vec3(0,0,0);
    data.pos = vec3(0, 0, 0);
    
    return data;
}