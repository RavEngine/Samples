$input a_position, a_normal, a_texcoord0, i_data0, i_data1, i_data2, i_data3
$output v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    // give every instance a randomish rotation speed
    float theta = u_time.x * M_PI/4 * rand(vec2(gl_InstanceID % 10, gl_InstanceID % 3));
    float scaleInput = u_time.x * M_PI/4 * rand(vec2(gl_InstanceID % 3, gl_InstanceID % 7));
    
    float ct = cos(theta);
    float st = sin(theta);
    
    float ss = sin(scaleInput) / 2 + 0.8;
    float cs = cos(scaleInput) / 2 + 0.8;
  
    // calculate rotation matrices and apply to a_position
    mat4 rotmatx = mtxFromRows(
        vec4(1,0,0,0),
        vec4(0,ct,-st,0),
        vec4(0,st,ct,0),
        vec4(0,0,0,1)
    );
    
    mat4 rotmaty = mtxFromRows(
        vec4(ct,0,st,0),
        vec4(0,1,0,0),
        vec4(-st,0,ct,0),
        vec4(0,0,0,1)
    );
    
    mat4 fullrotmat = mul(rotmatx, rotmaty);
    
    mat4 transmat = mtxFromRows(
        vec4(1,0,0,st * 2),
        vec4(0,1,0,ct * 2),
        vec4(0,0,1,st * 2),
        vec4(0,0,0,1)
    );
    
    mat4 scalemat = mtxFromRows(
        vec4(ss,0,0,0),
        vec4(0,cs,0,0),
        vec4(0,0,ss,0),
        vec4(0,0,0,1)
    );
    
    mat4 fullmat = mul(transmat, mul(fullrotmat,scalemat));
        
    a_position = mul(fullmat, vec4(a_position,1)).xyz;
        
	vs_genmats();
	vs_store();
}
