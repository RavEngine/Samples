
layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;

layout(binding = 0) uniform sampler g_sampler;
layout(binding = 1) uniform texture2D t_diffuse;

layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;

LitOutput frag()
{
    LitOutput fs_out;

    fs_out.color = texture(sampler2D(t_diffuse, g_sampler), inUV);
    fs_out.normal = inNormal;

    return fs_out;
}


