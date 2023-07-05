
layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;


layout(std430, binding = 2) readonly buffer modelMatrixBuffer
{
	mat4 model[];
};


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

// per-instance
layout(location = 3) in uint inEntityID;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;


void main()
{
    vec3 a_position = inPosition;

    a_position.z += sin(ubo.time * 10 + a_position.x * -5) / 40;
    a_position.y += cos(ubo.time * 10 + a_position.x * -5) / 50;

    mat4 inModel = model[inEntityID];

	vec4 worldPos = inModel * vec4(a_position,1);
    gl_Position = ubo.viewProj * worldPos;
	outNormal = normalize(transpose(mat3(inModel)) * inNormal);

	outUV = inUV;

}
