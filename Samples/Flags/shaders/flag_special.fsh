$input v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

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

// step function w/ ceiling 
float stepc(float value, float steps){
    return remap(ceil(remap(value,0.0,1.0,0.0,steps)),0.0,steps,0.0,1.0);
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

vec3 calcMain(vec2 uv){
    // adjust the number of stripes
    const float stripes = 6.0;

    // calculate where to sample 
    float coord = hsbinfcufve(stepf(1.0-uv.y,stripes));
    
    // calculate color & brightness
    return hsb2rgb(vec3(coord,1.0,b(coord)));
    
}

vec3 calcAlt(vec2 uv){
     // green, white, blue
     vec3 col1 = vec3(0.24,0.54,0.44);
     vec3 col2 = vec3(1.0,1.0,1.0);
     vec3 col3 = vec3(0.22,0.13,0.45);
     
     float diff = 0.4;
     
     const float steps = 2.0;

     // gradient + step function
     vec3 colorTop = mix(col1,col2,stepf(1.0-remap(uv.y,1.0-diff,1.0,0.0,1.0),steps));
     vec3 colorBot = mix(col2,col3,stepc(1.0-remap(uv.y,0.0,diff,0.0,1.0),steps));
     
     return uv.y < 0.5 ? colorBot : colorTop;
}

void main()
{
    vec2 uv = 1 - v_texcoord0;  // model UVs are upside-down

    // "rounded square wave" blending function
    float factor = (atan(sin(3*u_time[0])/0.1))/3+0.5;
    
    vec3 resCol = mix(calcMain(uv),calcAlt(uv),factor);
  
    PBR material = make_mat();
    material.color = resCol;
    material.normal = v_normal;
    material.position = v_worldpos;
    
    fs_store(material);
}


