
layout(location = 0) in vec2 inUV;

LitOutput frag()
{
	LitOutput mat_out;

	mat_out.color = vec4(1,0,0,1);

	mat_out.normal = vec3(0,0,1);

	mat_out.ao = 1;

	mat_out.roughness = 0.6;
	mat_out.specular = 0;
	mat_out.metallic = 0;
	mat_out.emissiveColor = vec3(0);

	return mat_out;
}
