
#include "ravengine_fsh.h"

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec4 outcolor;

layout(binding = 0) uniform sampler g_sampler;
layout(binding = 1) uniform texture2D t_tex;

void main()
{
    outcolor = texture(sampler2D(t_tex, g_sampler), inUV);
}

