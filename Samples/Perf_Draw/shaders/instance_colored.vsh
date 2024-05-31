
layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
    float time;
} ubo;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 v_position;

#define M_PI 3.1415926

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

LitVertexOut vert(EntityIn entity)
{    
    uint inEntityID = entity.entityID;
    mat4 worldTransform = entity.modelMtx;

     LitVertexOut vs_out;

    // give every instance a randomish rotation speed
    float theta = ubo.time * M_PI / 4 * rand(vec2(inEntityID % 10, inEntityID % 3));
    float scaleInput = ubo.time * M_PI / 4 * rand(vec2(inEntityID % 3, inEntityID % 7));
    
    float ct = cos(theta);
    float st = sin(theta);
    
    float ss = sin(scaleInput) / 2 + 0.8;
    float cs = cos(scaleInput) / 2 + 0.8;
  
    // calculate rotation matrices and apply to a_position
    mat4 rotmatx = mat4(
        vec4(1,0,0,0),
        vec4(0,ct,-st,0),
        vec4(0,st,ct,0),
        vec4(0,0,0,1)
    );
    
    mat4 rotmaty = mat4(
        vec4(ct,0,st,0),
        vec4(0,1,0,0),
        vec4(-st,0,ct,0),
        vec4(0,0,0,1)
    );
    
    mat4 fullrotmat = rotmatx * rotmaty;
    
    mat4 transmat = mat4(
        vec4(1,0,0,st * 2),
        vec4(0,1,0,ct * 2),
        vec4(0,0,1,st * 2),
        vec4(0,0,0,1)
    );
    
    mat4 scalemat = mat4(
        vec4(ss,0,0,0),
        vec4(0,cs,0,0),
        vec4(0,0,ss,0),
        vec4(0,0,0,1)
    );
    
    vec4 transformed = vec4(inPosition, 1);
    transformed = scalemat * transformed;
    transformed = fullrotmat * transformed;
    transformed = transpose(transmat) * transformed;
        
    transformed = worldTransform * vec4(transformed.xyz, 1);
    
    vs_out.position = ubo.viewProj * vec4(transformed.xyz, 1);
        
	outNormal = inNormal;
    v_position = transformed.xyz;

    return vs_out;
}
