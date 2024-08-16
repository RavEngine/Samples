
layout(binding = 0) uniform sampler g_sampler; 
layout(binding = 1) uniform texture2D t_spritesheet;

layout(location = 0) in vec2 inUV; 
layout(location = 1) in flat float alphaFactor;

UnlitOut frag(){
    UnlitOut fs_out;

    fs_out.color = texture(sampler2D(t_spritesheet, g_sampler), inUV);

    if (fs_out.color.a < 0.5){
        discard;
    }

    fs_out.color.a *= alphaFactor;

    return fs_out;
}
