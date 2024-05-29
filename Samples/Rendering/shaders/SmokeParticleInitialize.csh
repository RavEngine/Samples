
struct ParticleData{
    vec3 pos;
    vec2 scale;
    uint animationFrame;
};

float rand(in vec2 ip) {
    const float seed = 12345678;
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


ParticleData init(ParticleInitData initData)
{  
    uint particleID = initData.particleID;

    ParticleData data;
    data.scale = vec2(0.1,0.1);
    vec4 pos = vec4(
        rand(vec2(particleID,particleID)),
        rand(vec2(particleID * 2,particleID * 2)),
        rand(vec2(particleID / 2,particleID / 2)),
        1
    );

    pos = initData.emitterModel * pos;

    data.pos = pos.xyz;

    data.animationFrame = 0;

    return data;
}