
layout(location = 0) in float mixFactor;

layout(push_constant) uniform UniformBufferObject{
	float time;
} ubo;

LitOutput frag(EnvironmentData envData)
{
    LitOutput fs_out;

    fs_out.color = vec4(mix(vec3(110/255.0, 219/255.0, 0),vec3(33/255.0, 143/255.0, 0),mixFactor),1);
    fs_out.normal = vec3(0,0,1);
    fs_out.roughness = 0.5;
	fs_out.specular = 0.2;
	fs_out.metallic = 0;
	fs_out.ao = 1;
    fs_out.emissiveColor = vec3(0);

    return fs_out;
}
