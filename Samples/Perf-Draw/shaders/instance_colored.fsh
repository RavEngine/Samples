$input v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

SAMPLER2D(s_albedoTex,0);
uniform vec4 albedoColor;

void main()
{
	int index_id = abs(v_worldpos.x * 100);
	
	PBR material = make_mat();
	material.color = v_worldpos / 200;
	material.normal = v_normal;
	material.position = v_worldpos;
	
	fs_store(material);
}

