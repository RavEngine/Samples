

UnlitVertexOut vert(EntityIn entity, EngineData data)
{
    UnlitVertexOut vs_out;

    vec4 worldPos = entity.modelMtx * vec4(inPosition,1);
    vs_out.position = data.viewProj * worldPos;

    return vs_out;
}
