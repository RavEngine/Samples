
#include "RavEngine/billboard.glsl"

layout(push_constant, std430) uniform UniformBufferObject{
    ivec2 spritesheetDim;
    ivec2 numSprites;
    uint bytesPerParticle;
    uint particlePositionOffset;
    uint particleScaleOffset;
    uint particleFrameOffset;
    uint particleAlphaOffset;
} ubo;

layout(location = 0) out vec2 out_uv; 
layout(location = 1) out flat float alphaFactor; 

ParticleVertexOut vert(uint particleID, ParticleMatrices matrices, vec2 inVertex){

    BillboardVertexResult vertdata = billboard_vert(particleID, matrices, inVertex,
        ubo.spritesheetDim, ubo.numSprites,
        ubo.bytesPerParticle, ubo.particlePositionOffset, ubo.particleScaleOffset, ubo.particleFrameOffset
    );

    ParticleVertexOut v_out;

    v_out.localPosition = vertdata.localPosition;
    out_uv = vertdata.uv;

    const uint particleDataOffset = (particleID * ubo.bytesPerParticle) / 4;
    const uint particleAlphaOffset = particleDataOffset + ubo.particleAlphaOffset / 4;

    alphaFactor = uintBitsToFloat(particleDataBytes[particleAlphaOffset]);
   
    return v_out;
}
