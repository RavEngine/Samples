
layout(location = 0) out vec2 outUV;

UnlitVertexOut vert(EntityIn entity, EngineData data)
{
    UnlitVertexOut vs_out;

    outUV = inUV;

    vs_out.localPosition = inPosition;

    return vs_out;
}
