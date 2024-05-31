
layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 v_position;

layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
	float time;
} ubo;

LitOutput frag()
{
	LitOutput fs_out;
	fs_out.color = vec4(v_position / 200,1);
	fs_out.normal = inNormal;
	return fs_out;
}

