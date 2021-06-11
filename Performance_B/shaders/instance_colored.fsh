$input v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

SAMPLER2D(s_albedoTex,0);
uniform vec4 albedoColor;

void main()
{
	int index_id = v_texcoord0.x;
	
	PBR material = make_mat();
	material.color = vec3((index_id % 255)/255.0,(index_id % 128)/128.0,(index_id % 64)/64.0) * albedoColor;
	material.normal = v_normal;
	material.position = v_worldpos;
	
	fs_store(material);
}

