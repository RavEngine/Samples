$input a_position, a_normal, a_texcoord0, i_data0, i_data1, i_data2, i_data3
$output v_normal, v_texcoord0, v_worldpos

#include "ravengine_shader.glsl"

void main()
{
	vs_genmats();
	
	v_texcoord0.x = gl_InstanceID;
	
	vs_store();
}
