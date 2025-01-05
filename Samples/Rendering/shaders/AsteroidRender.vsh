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

ParticleVertexOut vert(uint particleID, ParticleMatrices matrices){

    MeshParticleVertexOut mesh_out = mesh_particle_vert(particleID, matrices,
        ubo.bytesPerParticle, ubo.positionOffset, ubo.scaleOffset, ubo.rotationOffset
    );

    outUV = inUV;

    ParticleVertexOut vs_out;
    vs_out.localPosition = mesh_out.localPosition;
    
    const uint particleDataOffset = (particleID * ubo.bytesPerParticle) / 4;
    const uint alphaOffset = particleDataOffset + ubo.alphaOffset / 4;

    alphaFactor = uintBitsToFloat(particleDataBytes[alphaOffset]);

    return vs_out;
}