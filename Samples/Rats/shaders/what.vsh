
layout(location = 0) out vec2 outUV;

UnlitVertexOut vert(EntityIn entity, EngineData data)
{
    UnlitVertexOut vs_out;

    vec4 worldPos = entity.modelMtx * vec4(inPosition,1);

    outUV = inUV;

    vs_out.position = data.viewProj * worldPos;

    return vs_out;
}
