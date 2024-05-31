
layout(location = 0) in vec2 inUV;

layout(binding = 0) uniform sampler g_sampler;
layout(binding = 1) uniform texture2D t_tex;

UnlitOut frag()
{
    UnlitOut fs_out;
    fs_out.color = texture(sampler2D(t_tex, g_sampler), inUV);

    return fs_out;
}

