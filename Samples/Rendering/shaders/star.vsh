
layout(push_constant, std430) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;

layout(location = 0) out vec2 outUV;

UnlitVertexOut vertex(EntityIn entity)
{
    UnlitVertexOut vs_out;

    vec4 worldPos = entity.modelMtx * vec4(inPosition,1);
    
    outUV = inUV;

    vs_out.position = ubo.viewProj * worldPos;

    return vs_out;
}
