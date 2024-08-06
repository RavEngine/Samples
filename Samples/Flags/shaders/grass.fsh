
layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in float mixFactor;

layout(push_constant) uniform UniformBufferObject{
	float time;
} ubo;

LitOutput frag()
{
    LitOutput fs_out;

    fs_out.color = vec4(mix(vec3(110/255.0, 219/255.0, 0),vec3(33/255.0, 143/255.0, 0),mixFactor),1);
    fs_out.normal = inNormal;

    return fs_out;
}
