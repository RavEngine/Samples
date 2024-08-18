
layout(location = 0) in vec2 inUV;
layout(location = 1) in vec3[3] inTBN;

vec3 colors[] = {
    vec3(0.3,0,0),
    vec3(0,0.3,0),
    vec3(0,0,0.3)
};

LitOutput frag()
{
	LitOutput mat_out;

	mat_out.color = vec4(colors[0],0.5);

    mat3 TBN = mat3(inTBN[0],inTBN[1],inTBN[2]);
	mat_out.normal = normalize(TBN * vec3(0,0,1));

	mat_out.ao = 0;

	mat_out.roughness = 0;
	mat_out.specular = 0.8;
	mat_out.metallic = 0.2;
	mat_out.emissiveColor = vec3(0,0,0);

	return mat_out;
}