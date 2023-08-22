#include "ravengine_vsh.h"

layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;


VS_INPUTS()

layout(location = 0) out
vec3 outNormal;
layout(location = 1) out vec2 outUV;
layout(location = 2) out float mixFactor;

void main()
{
    mat4 inModel = model[inEntityID];
    vec3 a_position = inPosition;
    vec4 worldPos = inModel * vec4(a_position, 1);

    const float height = 3.43;
    const float extentFactor = 0.5;

    a_position.x += sin(ubo.time * -5 + worldPos.x + worldPos.z) * (a_position.y / height) * extentFactor;
    worldPos = inModel * vec4(a_position, 1);

    gl_Position = ubo.viewProj * worldPos;

	outNormal = normalize(transpose(mat3(inModel)) * inNormal);
    mixFactor = height - a_position.y;
}
