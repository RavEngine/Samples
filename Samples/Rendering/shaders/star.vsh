
layout(push_constant, std430) uniform UniformBufferObject{
    float time;
} ubo;

layout(location = 0) out vec2 outUV;

UnlitVertexOut vert(EntityIn entity, EngineData data)
{
    UnlitVertexOut vs_out;

    vs_out.localPosition = inPosition;
    outUV = inUV;

    return vs_out;
}
