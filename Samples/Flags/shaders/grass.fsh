$input v_normal, v_worldpos, mixFactor

#include "ravengine_shader.glsl"

void main()
{
    PBR material = make_mat();
    material.color = mix(vec3(110/255.0, 219/255.0, 0),vec3(33/255.0, 143/255.0, 0),mixFactor);
    material.normal = v_normal;
    material.position = v_worldpos;
    
    fs_store(material);
}


