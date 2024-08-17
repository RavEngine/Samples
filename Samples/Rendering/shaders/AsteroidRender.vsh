layout(push_constant, std430) uniform UniformBufferObject{
    uint bytesPerParticle;
    uint positionOffset;
    uint scaleOffset;
    uint rotationOffset;
    uint alphaOffset;
} ubo;

#include "RavEngine/meshparticle.glsl"

layout(location = 0) out vec2 outUV;
layout(location = 1) out flat float alphaFactor;
layout(location = 2) out vec3[3] outTBN;

ParticleVertexOut vert(uint particleID, ParticleMatrices matrices){

    MeshParticleVertexOut mesh_out = mesh_particle_vert(particleID, matrices,
        ubo.bytesPerParticle, ubo.positionOffset, ubo.scaleOffset, ubo.rotationOffset
    );

    outUV = inUV;

    outTBN[0] = mesh_out.T;
    outTBN[1] = mesh_out.B;
    outTBN[2] = mesh_out.N;

    ParticleVertexOut vs_out;
    vs_out.position = mesh_out.position;
    vs_out.worldPosition = mesh_out.worldPosition;
    
    const uint particleDataOffset = (particleID * ubo.bytesPerParticle) / 4;
    const uint alphaOffset = particleDataOffset + ubo.alphaOffset / 4;

    alphaFactor = uintBitsToFloat(particleDataBytes[alphaOffset]);

    return vs_out;
}