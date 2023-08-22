#include "ravengine_fsh.h"

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;

FS_OUTPUTS()

layout(binding = 0) uniform sampler g_sampler;
layout(binding = 1) uniform texture2D t_diffuse;

layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;

void main()
{
    outcolor = texture(sampler2D(t_diffuse, g_sampler), inUV);
    outnormal = vec4(inNormal,1);
}


