#extension GL_GOOGLE_include_directive : enable

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec4 outColor;

// adapted from "Warped perlin noise animated" by Sergio_2357 https://www.shadertoy.com/view/cdd3RX
uint hash(uint s) {
    s ^= 2747636419u;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    return s;
}

float Fade(float t) {
    return smoothstep(0.0, 1.0, t);
}

float Lerp(float t, float a, float b) {
    return a + t*(b-a);
}

float randVal(uint x, uint y) {
    uint rand = hash(x^y)^hash(x)^hash(y);
    float fv = float(rand%1000000u)/1000000.0;
    return fv;
    /*int h = int(rand)%4;
    if(h == 0)
        return vec2(1.0, 1.0);
    else if(h == 1)
        return vec2(-1.0, 1.0);
    else if(h == 2)
        return vec2(-1.0, -1.0);
    else
        return vec2(1.0, -1.0);*/
}

float perlinNoise(vec2 p) {
    int xl = int(floor(p.x));
    int xh = int(ceil(p.x));
    int yl = int(floor(p.y));
    int yh = int(ceil(p.y));
    /*float v1 = dot(randVec(uint(xl), uint(yl)), p-vec2(xl, yl))*0.5+0.5;
    float v2 = dot(randVec(uint(xh), uint(yl)), p-vec2(xh, yl))*0.5+0.5;
    float v3 = dot(randVec(uint(xl), uint(yh)), p-vec2(xl, yh))*0.5+0.5;
    float v4 = dot(randVec(uint(xh), uint(yh)), p-vec2(xh, yh))*0.5+0.5;*/
    float v1 = randVal(uint(xl), uint(yl));
    float v2 = randVal(uint(xh), uint(yl));
    float v3 = randVal(uint(xl), uint(yh));
    float v4 = randVal(uint(xh), uint(yh));
    float xf = p.x-floor(p.x);
    float yf = p.y-floor(p.y);
    float u = Fade(xf);
    float v = Fade(yf);
    return Lerp(v,
            Lerp(u, v1, v2),
            Lerp(u, v3, v4));
}

mat2 rt = mat2(0.7071067, -0.7071067, 0.7071067, 0.7071067);

float rotatedPerlinNoise(vec2 p) {
    return (perlinNoise(p)+perlinNoise(p*rt+vec2(1000.0, 1000.0)))/2.0;
}

float fractalPerlinNoise(vec2 p) {
    int steps = 3;
    float val = rotatedPerlinNoise(p);
    float sig = 0.4;
    float sigmlt = 0.4;
    float scale = 2.0;
    float scalemlt = 2.0;
    for (int i = 0; i < steps; i++) {
        val = val*(1.0-sig)+sig*rotatedPerlinNoise(p*scale);
        sig *= sigmlt;
        scale *= scalemlt;
    }
    return val;
}

float warpedPerlinNoise(vec2 p) {
    float deg = fractalPerlinNoise(p);
    float cs = cos(deg);
    float sn = sin(deg);
    mat2 rot = mat2(cs, -sn, sn, cs);
    int steps = 2;
    float mlt = 4.0;
    vec2 add = vec2(0.0, 0.0);
    vec2 inc = vec2(5.2, 6.2);
    vec2 mv = vec2(0, 0);
    for (int i = 0; i < steps; i++) {
        vec2 tmp = mv;
        mv.x = fractalPerlinNoise(p + rot*mv*mlt + add);
        add += inc;
        mv.y = fractalPerlinNoise(p + rot*mv*mlt + add);
        add += inc;
    }
    return mv.x;
}

vec4 colFromGreyscale(float f) {
    vec4 col0 = vec4(0.7, 0.0, 0.0, 1.0);
    vec4 col1 = vec4(1.3, 1.0, 0.0, 1.0);
    vec4 res = col0*f+(1.0-f)*col1;
    return res;
}

void main() {
    
    float timeSinceStart = 0;// ubo.timeSinceStart;
    
    vec2 uv = inUV;
    
    uv.x *= 20.0;
    uv.y *= 10.0;
    uv += vec2(35.0, 35.0);
    float col = warpedPerlinNoise(uv + timeSinceStart * 0.1);
    vec3 color = colFromGreyscale(col).xyz;
    
    outColor = vec4(color, 1.0);
}
