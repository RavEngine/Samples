
layout(push_constant) uniform UniformBufferObject{
    float time;
} ubo;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;

LitVertexOut vert(EntityIn entity, EngineData data)
{
    mat4 inModel = entity.modelMtx;
    LitVertexOut vs_out;

    vec3 a_position = inPosition;

    a_position.z += sin(ubo.time * 10 + a_position.x * -5) / 40;
    a_position.y += cos(ubo.time * 10 + a_position.x * -5) / 50;

    vs_out.localPosition = a_position;
	outNormal = inNormal;

	outUV = inUV;
    return vs_out;
}
