$input v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

SAMPLER2D(s_albedoTex,0);

// adjust the number of stripes
const float stripes = 6.0;

//  Function from Iñigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0,1.0,1.0), rgb, c.y);
}


// linear value remap
float remap(float value, float low1, float high1, float low2, float high2){
    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

// step function w/ floor
float stepf(float value,float steps){
    return remap(floor(remap(value,0.0,1.0,0.0,steps)),0.0,steps,0.0,1.0);
}

// used to control position on the rainbow
float hsbinfcufve(float x){
    return pow(x,1.5);
}

// used to control brightness
float b(float x){
    return 1.0 - pow(x,3.0);
}

// prevent wraparound
float clampInRange(float x){
    return ((x >= 0.0 && x <= 1.0) ? x : 0.0);
}

void main()
{
    
    vec2 uv = v_texcoord0;
    
    // calculate where to sample 
    float coord = hsbinfcufve(stepf(1.0-uv.y,stripes));
    
    // calculate color & brightness
    vec3 resCol = hsb2rgb(vec3(coord,1.0,b(coord)));
    
    PBR material = make_mat();
    material.color = resCol;
    material.normal = v_normal;
    material.position = v_worldpos;
    
    fs_store(material);
}


