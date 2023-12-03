#include "ravengine_vsh.h"

layout(push_constant, std430) uniform UniformBufferObject{
    mat4 viewProj;
} ubo;

VS_INPUTS()

layout(location = 0) out vec2 outUV;

void main()
{
    mat4 inModel = model[inEntityID];

    vec4 worldPos = inModel * vec4(inPosition,1);
    
    outUV = inUV;

    gl_Position = ubo.viewProj * worldPos;

}
