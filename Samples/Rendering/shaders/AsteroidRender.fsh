layout(push_constant, std430) uniform UniformBufferObject{
    uint bytesPerParticle;
    uint positionOffset;
    uint scaleOffset;
    uint rotationOffset;
    uint alphaOffset;
} ubo;

layout(location = 0) in vec2 inUV;
layout(location = 1) in flat float alphaFactor;
layout(location = 2) in vec3[3] inTBN;


// adapted from "5 procedural textures" by ianertson https://www.shadertoy.com/view/csyGzw
float rand(in vec2 ip, in float seed) {
    uvec2 p = uvec2(floatBitsToUint(ip.x), floatBitsToUint(ip.y));
    uint s = floatBitsToUint(seed);
    s ^= (s ^ ((~p.x << s) + (~p.y << s)));
    
    p ^= (p << 17U);
    p ^= ((p ^ s) >> 13U);
    p ^= (p << 5U);
    p ^= ((s + (s&(p.x^p.y))) >> 3U);
    
    uint n = (p.x*s+p.y)+((p.x ^ p.y) << ~p.x ^ s) + ((p.x ^ p.y) << ~p.y ^ s);
    return float(n*50323U) / float(0xFFFFFFFFU);
}

float xnoise(in vec2 p, in float seed) {
    vec2 id = floor(p);
    vec2 lv = fract(p);
    lv = lv*lv*(3.0-2.0*lv);
    return mix(
        mix(rand(id, seed), rand(id+vec2(1, 0), seed), lv.x),
        mix(rand(id + vec2(0, 1), seed), rand(id + vec2(1, 1), seed), lv.x),
        lv.y
    );
}


float xnoise(in vec2 p, in float seed, in float freq, const in int levels) {
    float div = 0.0;
    float amp = 1.0;
    float n = 0.0;
    
    for (int i = 0; i < levels; i++) {
        n += amp*xnoise(p*freq, seed); div += amp; amp /= 2.0; freq *= 2.0;
    }
    
    return n / div;
}

vec3 trand(in vec2 p, in float seed, in float lod) {
    return vec3(rand(p*seed, seed));
}


vec3 snoise(in vec2 p, in float seed, in float lod) {
    vec2 id = floor(p);
    vec2 lv = fract(p);
    lv = lv*lv*(3.0-2.0*lv);
    return mix(
        mix(trand(id, seed, lod), trand(id+vec2(1, 0), seed, lod), lv.x),
        mix(trand(id + vec2(0, 1), seed, lod), trand(id + vec2(1, 1), seed, lod), lv.x),
        lv.y
    );
}


vec3 snoise(in vec2 p, in float seed, in float lod, in float freq, const in int levels) {
    float div = 0.0;
    float amp = 1.0;
    vec3 n = vec3(0.0);
    
    for (int i = 0; i < levels; i++) {
        n += amp*snoise(p*freq, seed, lod); div += amp; amp /= 2.0; freq *= 2.0; lod /= 2.0;
    }
    
    return n / div;
}

vec3 snoiseWarp(in vec2 p, in float seed, in float lod, in float freq, in float warp, const in int levels) {
    float div = 0.0;
    float amp = 1.0;
    vec3 n = vec3(0.0);
    
    for (int i = 0; i < levels; i++) {
        n += amp*snoise(p*freq, seed, lod); div += amp; amp /= 2.0; freq *= 2.0; lod /= 2.0;
        p += ((n.xy*(0.5+(0.5*n.z)))*2.0-1.0)*warp;
    }
    
    return n / div;
}


vec3 rockTexture(in vec2 uv) {
    vec3 col = vec3(0.0);
    vec3 grain = vec3(rand(uv,0));
    float h = xnoise(uv, 203.231, 16.0, 4);
    grain = (grain+h)/2.;
    vec3 lf1 = snoiseWarp(uv, 0.032123, 0.5, 4.5, 1.5, 4);
    vec3 lf2 = snoise(uv, 1.1112312, 0.01, 16.0, 4);
    
    vec3 c1 = vec3(106, 104, 105) / 255;
    vec3 c2 = vec3(120, 114, 109) / 255;
    vec3 c3 = vec3(133, 113, 92) / 255;
    vec3 c4 = vec3(83, 81, 75) / 255;
    
    vec3 col1 = mix(mix(mix(c1, c2, grain.x), c3, grain.y), c4, grain.z);
    col1 = mix(col1, vec3(1.), lf1.x*lf1.x*h*grain.x);
    col += col1;
    
    float edge = abs(lf2.x*2.0-1.0);
    edge = max(0.0, 1.0-smoothstep(0.02, 0.09, edge));
    
    float scratchReg = edge*lf1.y*h*grain.y;
    col = mix(col, col*col, scratchReg);
        
    return col;
}


LitOutput frag()
{
	LitOutput mat_out;

	mat_out.color = vec4(rockTexture(inUV),alphaFactor);

	mat3 TBN = mat3(inTBN[0],inTBN[1],inTBN[2]);
	mat_out.normal = normalize(TBN * vec3(0,0,1));

	float specular = 0.1;
	float metallic = 0.1;
	float roughness = 0.8;
	mat_out.ao = 1;

	mat_out.roughness =  0.8;
	mat_out.specular = 0.1;
	mat_out.metallic =  0.1;

	return mat_out;
}
