#include "AsteroidShared.glsl"

#include "utility.glsl"

ParticleData init(ParticleInitData initData)
{
    uint particleID = initData.particleID;

    ParticleData data;
   
    data.velocity = normalize(vec3(
            rand(vec2(particleID,particleID)) * 2 - 1,
            rand(vec2(particleID+1,particleID+1)),
            rand(vec2(particleID+2,particleID+2)) * 2 - 1
    )) * 0.2;
    data.rot = vec4(0,0,0,1);
    data.scale = vec3(rand(vec2(particleID,particleID))) * 0.4 + 0.2;
    data.pos = (initData.emitterModel * vec4(0, 0, 0, 1)).xyz;
    
    return data;
}