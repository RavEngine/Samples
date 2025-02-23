
layout(location = 0) in vec2 inUV;

layout(binding = 0) uniform sampler g_sampler;
layout(binding = 1) uniform texture2D t_diffuse;

layout(push_constant) uniform UniformBufferObject{
    float time;
} ubo;

LitOutput frag(EnvironmentData envData)
{
    LitOutput fs_out;

    fs_out.color = texture(sampler2D(t_diffuse, g_sampler), inUV);
    fs_out.normal = vec3(0,0,1);
    fs_out.roughness = 0.5;
	fs_out.specular = 0.2;
	fs_out.metallic = 0;
	fs_out.ao = 1;
    fs_out.emissiveColor = vec3(0);

    return fs_out;
}


