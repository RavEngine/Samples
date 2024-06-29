#include "utility.glsl"
#include "AsteroidShared.glsl"

uint choose_mesh(in ParticleData data, uint particleID){

    uint ID = uint(round(rand(vec2(particleID,particleID)) * 3));

    return ID;
}