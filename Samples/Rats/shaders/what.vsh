
layout(push_constant, std430) uniform UniformBufferObject{
    mat4 viewProj;
} ubo;

layout(location = 0) out vec2 outUV;

UnlitVertexOut vert(EntityIn entity)
{
    UnlitVertexOut vs_out;

    vec4 worldPos = entity.modelMtx * vec4(inPosition,1);

    outUV = inUV;

    vs_out.position = ubo.viewProj * worldPos;

    return vs_out;
}
