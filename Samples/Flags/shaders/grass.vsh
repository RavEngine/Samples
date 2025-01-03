layout(push_constant) uniform UniformBufferObject{
    float time;
} ubo;

layout(location = 0) out float mixFactor;

LitVertexOut vert(EntityIn entity, EngineData data)
{
    mat4 inModel = entity.modelMtx;
    LitVertexOut vs_out;

    vec3 a_position = inPosition;
    vec4 worldPos = inModel * vec4(a_position, 1);

    const float height = 3.43;
    const float extentFactor = 0.5;

    a_position.x += sin(ubo.time * -5 + worldPos.x + worldPos.z) * (a_position.y / height) * extentFactor;
    vs_out.localPosition = a_position;

    mixFactor = height - a_position.y;

    return vs_out;
}
