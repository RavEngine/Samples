layout(push_constant) uniform UniformBufferObject{
    mat4 viewProj;
	vec4 colorTint;
    float time;
} ubo;


layout(std430, binding = 2) readonly buffer modelMatrixBuffer
{
	mat4 model[];
};


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

// per-instance
layout(location = 3) in uint inEntityID;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 v_position;

#define M_PI 3.1415926

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    // give every instance a randomish rotation speed
    float theta = ubo.time.x * M_PI/4 * rand(vec2(gl_InstanceID % 10, gl_InstanceID % 3));
    float scaleInput = ubo.time.x * M_PI/4 * rand(vec2(gl_InstanceID % 3, gl_InstanceID % 7));
    
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
    
    mat4 fullmat = transmat * (fullrotmat * scalemat);
        
    gl_Position = fullmat * vec4(inPosition,1);
        
	outNormal = inNormal;
    v_position = gl_Position.xyz;
}
