layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 v_position;

layout(location = 0) out vec4 outcolor;
layout(location = 1) out vec4 outnormal;


layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
	float time;
} ubo;

void main()
{
	outcolor = vec4(v_position / 200,1);
	outnormal = vec4(inNormal,1);
}

